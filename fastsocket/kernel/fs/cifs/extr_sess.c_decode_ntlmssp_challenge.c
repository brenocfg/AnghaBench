#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int len; int /*<<< orphan*/  response; } ;
struct cifs_ses {TYPE_3__ auth_key; TYPE_1__* ntlmssp; } ;
struct TYPE_6__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  BufferOffset; } ;
struct TYPE_8__ {char* Challenge; TYPE_2__ TargetInfoArray; int /*<<< orphan*/  NegotiateFlags; int /*<<< orphan*/  MessageType; int /*<<< orphan*/  Signature; } ;
struct TYPE_5__ {void* server_flags; int /*<<< orphan*/  cryptkey; } ;
typedef  TYPE_4__ CHALLENGE_MESSAGE ;

/* Variables and functions */
 unsigned int CIFS_CRYPTO_KEY_SIZE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NtLmChallenge ; 
 int /*<<< orphan*/  cERROR (int,char*,...) ; 
 int /*<<< orphan*/  kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int decode_ntlmssp_challenge(char *bcc_ptr, int blob_len,
				    struct cifs_ses *ses)
{
	unsigned int tioffset; /* challenge message target info area */
	unsigned int tilen; /* challenge message target info area length  */

	CHALLENGE_MESSAGE *pblob = (CHALLENGE_MESSAGE *)bcc_ptr;

	if (blob_len < sizeof(CHALLENGE_MESSAGE)) {
		cERROR(1, "challenge blob len %d too small", blob_len);
		return -EINVAL;
	}

	if (memcmp(pblob->Signature, "NTLMSSP", 8)) {
		cERROR(1, "blob signature incorrect %s", pblob->Signature);
		return -EINVAL;
	}
	if (pblob->MessageType != NtLmChallenge) {
		cERROR(1, "Incorrect message type %d", pblob->MessageType);
		return -EINVAL;
	}

	memcpy(ses->ntlmssp->cryptkey, pblob->Challenge, CIFS_CRYPTO_KEY_SIZE);
	/* BB we could decode pblob->NegotiateFlags; some may be useful */
	/* In particular we can examine sign flags */
	/* BB spec says that if AvId field of MsvAvTimestamp is populated then
		we must set the MIC field of the AUTHENTICATE_MESSAGE */
	ses->ntlmssp->server_flags = le32_to_cpu(pblob->NegotiateFlags);
	tioffset = le32_to_cpu(pblob->TargetInfoArray.BufferOffset);
	tilen = le16_to_cpu(pblob->TargetInfoArray.Length);
	if (tilen) {
		ses->auth_key.response = kmalloc(tilen, GFP_KERNEL);
		if (!ses->auth_key.response) {
			cERROR(1, "Challenge target info allocation failure");
			return -ENOMEM;
		}
		memcpy(ses->auth_key.response, bcc_ptr + tioffset, tilen);
		ses->auth_key.len = tilen;
	}

	return 0;
}