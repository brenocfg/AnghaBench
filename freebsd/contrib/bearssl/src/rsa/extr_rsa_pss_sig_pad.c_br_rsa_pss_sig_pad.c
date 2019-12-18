#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* generate ) (TYPE_1__ const**,unsigned char*,size_t) ;} ;
typedef  TYPE_1__ br_prng_class ;
struct TYPE_11__ {int /*<<< orphan*/  vtable; } ;
typedef  TYPE_2__ br_hash_compat_context ;
struct TYPE_12__ {int /*<<< orphan*/  (* out ) (int /*<<< orphan*/ *,unsigned char*) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,unsigned char*,size_t) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ br_hash_class ;

/* Variables and functions */
 size_t br_digest_size (TYPE_3__ const*) ; 
 int /*<<< orphan*/  br_mgf1_xor (unsigned char*,size_t,TYPE_3__ const*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__ const**,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,unsigned char*) ; 

uint32_t
br_rsa_pss_sig_pad(const br_prng_class **rng,
	const br_hash_class *hf_data, const br_hash_class *hf_mgf1,
	const unsigned char *hash, size_t salt_len,
	uint32_t n_bitlen, unsigned char *x)
{
	size_t xlen, hash_len;
	br_hash_compat_context hc;
	unsigned char *salt, *seed;

	hash_len = br_digest_size(hf_data);

	/*
	 * The padded string is one bit smaller than the modulus;
	 * notably, if the modulus length is equal to 1 modulo 8, then
	 * the padded string will be one _byte_ smaller, and the first
	 * byte will be set to 0. We apply these transformations here.
	 */
	n_bitlen --;
	if ((n_bitlen & 7) == 0) {
		*x ++ = 0;
	}
	xlen = (n_bitlen + 7) >> 3;

	/*
	 * Check that the modulus is large enough for the hash value
	 * length combined with the intended salt length.
	 */
	if (hash_len > xlen || salt_len > xlen
		|| (hash_len + salt_len + 2) > xlen)
	{
		return 0;
	}

	/*
	 * Produce a random salt.
	 */
	salt = x + xlen - hash_len - salt_len - 1;
	if (salt_len != 0) {
		(*rng)->generate(rng, salt, salt_len);
	}

	/*
	 * Compute the seed for MGF1.
	 */
	seed = x + xlen - hash_len - 1;
	hf_data->init(&hc.vtable);
	memset(seed, 0, 8);
	hf_data->update(&hc.vtable, seed, 8);
	hf_data->update(&hc.vtable, hash, hash_len);
	hf_data->update(&hc.vtable, salt, salt_len);
	hf_data->out(&hc.vtable, seed);

	/*
	 * Prepare string PS (padded salt). The salt is already at the
	 * right place.
	 */
	memset(x, 0, xlen - salt_len - hash_len - 2);
	x[xlen - salt_len - hash_len - 2] = 0x01;

	/*
	 * Generate the mask and XOR it into PS.
	 */
	br_mgf1_xor(x, xlen - hash_len - 1, hf_mgf1, seed, hash_len);

	/*
	 * Clear the top bits to ensure the value is lower than the
	 * modulus.
	 */
	x[0] &= 0xFF >> (((uint32_t)xlen << 3) - n_bitlen);

	/*
	 * The seed (H) is already in the right place. We just set the
	 * last byte.
	 */
	x[xlen - 1] = 0xBC;

	return 1;
}