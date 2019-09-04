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
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  char* caddr_t ;

/* Variables and functions */
 int SHA1_RESULTLEN ; 
 int /*<<< orphan*/  VERIFY (int) ; 

__attribute__((used)) static void
mptcp_generate_idsn(char *sha_digest, int sha_digest_len, caddr_t idsn,
    int idsn_len)
{
	VERIFY(idsn_len == sizeof (u_int64_t));
	VERIFY(sha_digest_len == SHA1_RESULTLEN);

	/*
	 * Least significant 64 bits of the SHA1 hash
	 */

	idsn[7] = sha_digest[12];
	idsn[6] = sha_digest[13];
	idsn[5] = sha_digest[14];
	idsn[4] = sha_digest[15];
	idsn[3] = sha_digest[16];
	idsn[2] = sha_digest[17];
	idsn[1] = sha_digest[18];
	idsn[0] = sha_digest[19];
	return;
}