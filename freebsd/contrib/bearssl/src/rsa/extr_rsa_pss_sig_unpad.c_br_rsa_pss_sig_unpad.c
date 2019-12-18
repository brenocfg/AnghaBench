#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {size_t nlen; scalar_t__* n; } ;
typedef  TYPE_1__ br_rsa_public_key ;
struct TYPE_10__ {int /*<<< orphan*/  vtable; } ;
typedef  TYPE_2__ br_hash_compat_context ;
struct TYPE_11__ {int /*<<< orphan*/  (* out ) (int /*<<< orphan*/ *,unsigned char*) ;int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,unsigned char*,size_t) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ br_hash_class ;

/* Variables and functions */
 int BIT_LENGTH (scalar_t__) ; 
 int EQ0 (int) ; 
 size_t br_digest_size (TYPE_3__ const*) ; 
 int /*<<< orphan*/  br_mgf1_xor (unsigned char*,size_t,TYPE_3__ const*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,unsigned char*) ; 

uint32_t
br_rsa_pss_sig_unpad(const br_hash_class *hf_data,
	const br_hash_class *hf_mgf1,
	const unsigned char *hash, size_t salt_len,
	const br_rsa_public_key *pk, unsigned char *x)
{
	size_t u, xlen, hash_len;
	br_hash_compat_context hc;
	unsigned char *seed, *salt;
	unsigned char tmp[64];
	uint32_t r, n_bitlen;

	hash_len = br_digest_size(hf_data);

	/*
	 * Value r will be set to a non-zero value is any test fails.
	 */
	r = 0;

	/*
	 * The value bit length (as an integer) must be strictly less than
	 * that of the modulus.
	 */
	for (u = 0; u < pk->nlen; u ++) {
		if (pk->n[u] != 0) {
			break;
		}
	}
	if (u == pk->nlen) {
		return 0;
	}
	n_bitlen = BIT_LENGTH(pk->n[u]) + ((uint32_t)(pk->nlen - u - 1) << 3);
	n_bitlen --;
	if ((n_bitlen & 7) == 0) {
		r |= *x ++;
	} else {
		r |= x[0] & (0xFF << (n_bitlen & 7));
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
	 * Check value of rightmost byte.
	 */
	r |= x[xlen - 1] ^ 0xBC;

	/*
	 * Generate the mask and XOR it into the first bytes to reveal PS;
	 * we must also mask out the leading bits.
	 */
	seed = x + xlen - hash_len - 1;
	br_mgf1_xor(x, xlen - hash_len - 1, hf_mgf1, seed, hash_len);
	if ((n_bitlen & 7) != 0) {
		x[0] &= 0xFF >> (8 - (n_bitlen & 7));
	}

	/*
	 * Check that all padding bytes have the expected value.
	 */
	for (u = 0; u < (xlen - hash_len - salt_len - 2); u ++) {
		r |= x[u];
	}
	r |= x[xlen - hash_len - salt_len - 2] ^ 0x01;

	/*
	 * Recompute H.
	 */
	salt = x + xlen - hash_len - salt_len - 1;
	hf_data->init(&hc.vtable);
	memset(tmp, 0, 8);
	hf_data->update(&hc.vtable, tmp, 8);
	hf_data->update(&hc.vtable, hash, hash_len);
	hf_data->update(&hc.vtable, salt, salt_len);
	hf_data->out(&hc.vtable, tmp);

	/*
	 * Check that the recomputed H value matches the one appearing
	 * in the string.
	 */
	for (u = 0; u < hash_len; u ++) {
		r |= tmp[u] ^ x[(xlen - salt_len - 1) + u];
	}

	return EQ0(r);
}