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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  br_rsa_public_key ;

/* Variables and functions */
 int BR_MAX_RSA_SIZE ; 
 int /*<<< orphan*/  br_rsa_i32_public (unsigned char*,size_t,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  br_rsa_pkcs1_sig_unpad (unsigned char*,size_t,unsigned char const*,size_t,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 

uint32_t
br_rsa_i32_pkcs1_vrfy(const unsigned char *x, size_t xlen,
	const unsigned char *hash_oid, size_t hash_len,
	const br_rsa_public_key *pk, unsigned char *hash_out)
{
	unsigned char sig[BR_MAX_RSA_SIZE >> 3];

	if (xlen > (sizeof sig)) {
		return 0;
	}
	memcpy(sig, x, xlen);
	if (!br_rsa_i32_public(sig, xlen, pk)) {
		return 0;
	}
	return br_rsa_pkcs1_sig_unpad(sig, xlen, hash_oid, hash_len, hash_out);
}