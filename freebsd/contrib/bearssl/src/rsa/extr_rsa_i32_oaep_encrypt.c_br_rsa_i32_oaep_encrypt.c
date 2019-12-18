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
typedef  int /*<<< orphan*/  br_rsa_public_key ;
typedef  int /*<<< orphan*/  br_prng_class ;
typedef  int /*<<< orphan*/  br_hash_class ;

/* Variables and functions */
 scalar_t__ br_rsa_i32_public (void*,size_t,int /*<<< orphan*/  const*) ; 
 size_t br_rsa_oaep_pad (int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,void const*,size_t,int /*<<< orphan*/  const*,void*,size_t,void const*,size_t) ; 

size_t
br_rsa_i32_oaep_encrypt(
	const br_prng_class **rnd, const br_hash_class *dig,
	const void *label, size_t label_len,
	const br_rsa_public_key *pk,
	void *dst, size_t dst_max_len,
	const void *src, size_t src_len)
{
	size_t dlen;

	dlen = br_rsa_oaep_pad(rnd, dig, label, label_len,
		pk, dst, dst_max_len, src, src_len);
	if (dlen == 0) {
		return 0;
	}
	return dlen & -(size_t)br_rsa_i32_public(dst, dlen, pk);
}