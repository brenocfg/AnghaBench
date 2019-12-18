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
typedef  int /*<<< orphan*/  br_hash_class ;
typedef  int /*<<< orphan*/  br_ec_private_key ;
typedef  int /*<<< orphan*/  br_ec_impl ;

/* Variables and functions */
 int ORDER_LEN ; 
 size_t br_ecdsa_i15_sign_raw (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,void const*,int /*<<< orphan*/  const*,unsigned char*) ; 
 size_t br_ecdsa_raw_to_asn1 (unsigned char*,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,unsigned char*,size_t) ; 

size_t
br_ecdsa_i15_sign_asn1(const br_ec_impl *impl,
	const br_hash_class *hf, const void *hash_value,
	const br_ec_private_key *sk, void *sig)
{
	unsigned char rsig[(ORDER_LEN << 1) + 12];
	size_t sig_len;

	sig_len = br_ecdsa_i15_sign_raw(impl, hf, hash_value, sk, rsig);
	if (sig_len == 0) {
		return 0;
	}
	sig_len = br_ecdsa_raw_to_asn1(rsig, sig_len);
	memcpy(sig, rsig, sig_len);
	return sig_len;
}