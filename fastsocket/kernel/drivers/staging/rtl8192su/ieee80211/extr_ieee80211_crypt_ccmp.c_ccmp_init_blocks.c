#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct ieee80211_hdr_4addr {int* addr4; int* addr2; int* addr1; int /*<<< orphan*/  seq_ctl; int /*<<< orphan*/  frame_ctl; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int AES_BLOCK_LEN ; 
 int CCMP_PN_LEN ; 
 int ETH_ALEN ; 
 int IEEE80211_FCTL_FROMDS ; 
 int IEEE80211_FCTL_TODS ; 
 scalar_t__ IEEE80211_FTYPE_DATA ; 
 int WLAN_FC_GET_STYPE (int) ; 
 scalar_t__ WLAN_FC_GET_TYPE (int) ; 
 int /*<<< orphan*/  ieee80211_ccmp_aes_encrypt (struct crypto_tfm*,int*,int*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xor_block (int*,int*,int) ; 

__attribute__((used)) static void ccmp_init_blocks(struct crypto_tfm *tfm,
			     struct ieee80211_hdr_4addr *hdr,
			     u8 *pn, size_t dlen, u8 *b0, u8 *auth,
			     u8 *s0)
{
	u8 *pos, qc = 0;
	size_t aad_len;
	u16 fc;
	int a4_included, qc_included;
	u8 aad[2 * AES_BLOCK_LEN];

	fc = le16_to_cpu(hdr->frame_ctl);
	a4_included = ((fc & (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS)) ==
		       (IEEE80211_FCTL_TODS | IEEE80211_FCTL_FROMDS));
	/*
	qc_included = ((WLAN_FC_GET_TYPE(fc) == IEEE80211_FTYPE_DATA) &&
		       (WLAN_FC_GET_STYPE(fc) & 0x08));
        */
	// fixed by David :2006.9.6
	qc_included = ((WLAN_FC_GET_TYPE(fc) == IEEE80211_FTYPE_DATA) &&
		       (WLAN_FC_GET_STYPE(fc) & 0x80));
	aad_len = 22;
	if (a4_included)
		aad_len += 6;
	if (qc_included) {
		pos = (u8 *) &hdr->addr4;
		if (a4_included)
			pos += 6;
		qc = *pos & 0x0f;
		aad_len += 2;
	}
	/* CCM Initial Block:
	 * Flag (Include authentication header, M=3 (8-octet MIC),
	 *       L=1 (2-octet Dlen))
	 * Nonce: 0x00 | A2 | PN
	 * Dlen */
	b0[0] = 0x59;
	b0[1] = qc;
	memcpy(b0 + 2, hdr->addr2, ETH_ALEN);
	memcpy(b0 + 8, pn, CCMP_PN_LEN);
	b0[14] = (dlen >> 8) & 0xff;
	b0[15] = dlen & 0xff;

	/* AAD:
	 * FC with bits 4..6 and 11..13 masked to zero; 14 is always one
	 * A1 | A2 | A3
	 * SC with bits 4..15 (seq#) masked to zero
	 * A4 (if present)
	 * QC (if present)
	 */
	pos = (u8 *) hdr;
	aad[0] = 0; /* aad_len >> 8 */
	aad[1] = aad_len & 0xff;
	aad[2] = pos[0] & 0x8f;
	aad[3] = pos[1] & 0xc7;
	memcpy(aad + 4, hdr->addr1, 3 * ETH_ALEN);
	pos = (u8 *) &hdr->seq_ctl;
	aad[22] = pos[0] & 0x0f;
	aad[23] = 0; /* all bits masked */
	memset(aad + 24, 0, 8);
	if (a4_included)
		memcpy(aad + 24, hdr->addr4, ETH_ALEN);
	if (qc_included) {
		aad[a4_included ? 30 : 24] = qc;
		/* rest of QC masked */
	}

	/* Start with the first block and AAD */
	ieee80211_ccmp_aes_encrypt(tfm, b0, auth);
	xor_block(auth, aad, AES_BLOCK_LEN);
	ieee80211_ccmp_aes_encrypt(tfm, auth, auth);
	xor_block(auth, &aad[AES_BLOCK_LEN], AES_BLOCK_LEN);
	ieee80211_ccmp_aes_encrypt(tfm, auth, auth);
	b0[0] &= 0x07;
	b0[14] = b0[15] = 0;
	ieee80211_ccmp_aes_encrypt(tfm, b0, s0);
}