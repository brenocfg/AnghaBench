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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00lib_crypto {scalar_t__ cmd; int cipher; } ;
struct rt2x00_dev {int dummy; } ;
struct mac_iveiv_entry {int* iv; } ;
struct ieee80211_key_conf {int flags; int keyidx; int /*<<< orphan*/  hw_key_idx; } ;
typedef  int /*<<< orphan*/  iveiv_entry ;

/* Variables and functions */
 int CIPHER_AES ; 
 int CIPHER_TKIP ; 
 int CIPHER_TKIP_NO_MIC ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 int /*<<< orphan*/  MAC_IVEIV_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_WCID_ATTRIBUTE_CIPHER ; 
 int /*<<< orphan*/  MAC_WCID_ATTRIBUTE_CIPHER_EXT ; 
 int /*<<< orphan*/  MAC_WCID_ATTRIBUTE_KEYTAB ; 
 int /*<<< orphan*/  MAC_WCID_ATTRIBUTE_RX_WIUDF ; 
 int /*<<< orphan*/  MAC_WCID_ATTR_ENTRY (int /*<<< orphan*/ ) ; 
 scalar_t__ SET_KEY ; 
 int /*<<< orphan*/  memset (struct mac_iveiv_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2800_register_multiwrite (struct rt2x00_dev*,int /*<<< orphan*/ ,struct mac_iveiv_entry*,int) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2800_config_wcid_attr_cipher(struct rt2x00_dev *rt2x00dev,
					   struct rt2x00lib_crypto *crypto,
					   struct ieee80211_key_conf *key)
{
	struct mac_iveiv_entry iveiv_entry;
	u32 offset;
	u32 reg;

	offset = MAC_WCID_ATTR_ENTRY(key->hw_key_idx);

	if (crypto->cmd == SET_KEY) {
		rt2800_register_read(rt2x00dev, offset, &reg);
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_KEYTAB,
				   !!(key->flags & IEEE80211_KEY_FLAG_PAIRWISE));
		/*
		 * Both the cipher as the BSS Idx numbers are split in a main
		 * value of 3 bits, and a extended field for adding one additional
		 * bit to the value.
		 */
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_CIPHER,
				   (crypto->cipher & 0x7));
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_CIPHER_EXT,
				   (crypto->cipher & 0x8) >> 3);
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_RX_WIUDF, crypto->cipher);
		rt2800_register_write(rt2x00dev, offset, reg);
	} else {
		/* Delete the cipher without touching the bssidx */
		rt2800_register_read(rt2x00dev, offset, &reg);
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_KEYTAB, 0);
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_CIPHER, 0);
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_CIPHER_EXT, 0);
		rt2x00_set_field32(&reg, MAC_WCID_ATTRIBUTE_RX_WIUDF, 0);
		rt2800_register_write(rt2x00dev, offset, reg);
	}

	offset = MAC_IVEIV_ENTRY(key->hw_key_idx);

	memset(&iveiv_entry, 0, sizeof(iveiv_entry));
	if ((crypto->cipher == CIPHER_TKIP) ||
	    (crypto->cipher == CIPHER_TKIP_NO_MIC) ||
	    (crypto->cipher == CIPHER_AES))
		iveiv_entry.iv[3] |= 0x20;
	iveiv_entry.iv[3] |= key->keyidx << 6;
	rt2800_register_multiwrite(rt2x00dev, offset,
				      &iveiv_entry, sizeof(iveiv_entry));
}