#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  num_rounds; int /*<<< orphan*/  skey; } ;
typedef  TYPE_1__ br_aes_ct_ctrcbc_keys ;

/* Variables and functions */
 int /*<<< orphan*/  br_aes_ct_bitslice_encrypt (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  br_aes_ct_ortho (int*) ; 
 int /*<<< orphan*/  br_aes_ct_skey_expand (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int br_dec32be (unsigned char*) ; 
 int br_dec32le (unsigned char*) ; 
 int /*<<< orphan*/  br_enc32be (unsigned char*,int) ; 
 int /*<<< orphan*/  br_enc32le (unsigned char*,int) ; 
 int br_swap32 (int) ; 

void
br_aes_ct_ctrcbc_encrypt(const br_aes_ct_ctrcbc_keys *ctx,
	void *ctr, void *cbcmac, void *data, size_t len)
{
	/*
	 * When encrypting, the CBC-MAC processing must be lagging by
	 * one block, since it operates on the encrypted values, so
	 * it must wait for that encryption to complete.
	 */

	unsigned char *buf;
	unsigned char *ivbuf;
	uint32_t iv0, iv1, iv2, iv3;
	uint32_t cm0, cm1, cm2, cm3;
	uint32_t sk_exp[120];
	int first_iter;

	br_aes_ct_skey_expand(sk_exp, ctx->num_rounds, ctx->skey);

	/*
	 * We keep the counter as four 32-bit values, with big-endian
	 * convention, because that's what is expected for purposes of
	 * incrementing the counter value.
	 */
	ivbuf = ctr;
	iv0 = br_dec32be(ivbuf +  0);
	iv1 = br_dec32be(ivbuf +  4);
	iv2 = br_dec32be(ivbuf +  8);
	iv3 = br_dec32be(ivbuf + 12);

	/*
	 * The current CBC-MAC value is kept in little-endian convention.
	 */
	cm0 = br_dec32le((unsigned char *)cbcmac +  0);
	cm1 = br_dec32le((unsigned char *)cbcmac +  4);
	cm2 = br_dec32le((unsigned char *)cbcmac +  8);
	cm3 = br_dec32le((unsigned char *)cbcmac + 12);

	buf = data;
	first_iter = 1;
	while (len > 0) {
		uint32_t q[8], carry;

		/*
		 * The bitslice implementation expects values in
		 * little-endian convention, so we have to byteswap them.
		 */
		q[0] = br_swap32(iv0);
		q[2] = br_swap32(iv1);
		q[4] = br_swap32(iv2);
		q[6] = br_swap32(iv3);
		iv3 ++;
		carry = ~(iv3 | -iv3) >> 31;
		iv2 += carry;
		carry &= -(~(iv2 | -iv2) >> 31);
		iv1 += carry;
		carry &= -(~(iv1 | -iv1) >> 31);
		iv0 += carry;

		/*
		 * The odd values are used for CBC-MAC.
		 */
		q[1] = cm0;
		q[3] = cm1;
		q[5] = cm2;
		q[7] = cm3;

		br_aes_ct_ortho(q);
		br_aes_ct_bitslice_encrypt(ctx->num_rounds, sk_exp, q);
		br_aes_ct_ortho(q);

		/*
		 * We do the XOR with the plaintext in 32-bit registers,
		 * so that the value are available for CBC-MAC processing
		 * as well.
		 */
		q[0] ^= br_dec32le(buf +  0);
		q[2] ^= br_dec32le(buf +  4);
		q[4] ^= br_dec32le(buf +  8);
		q[6] ^= br_dec32le(buf + 12);
		br_enc32le(buf +  0, q[0]);
		br_enc32le(buf +  4, q[2]);
		br_enc32le(buf +  8, q[4]);
		br_enc32le(buf + 12, q[6]);

		buf += 16;
		len -= 16;

		/*
		 * We set the cm* values to the block to encrypt in the
		 * next iteration.
		 */
		if (first_iter) {
			first_iter = 0;
			cm0 ^= q[0];
			cm1 ^= q[2];
			cm2 ^= q[4];
			cm3 ^= q[6];
		} else {
			cm0 = q[0] ^ q[1];
			cm1 = q[2] ^ q[3];
			cm2 = q[4] ^ q[5];
			cm3 = q[6] ^ q[7];
		}

		/*
		 * If this was the last iteration, then compute the
		 * extra block encryption to complete CBC-MAC.
		 */
		if (len == 0) {
			q[0] = cm0;
			q[2] = cm1;
			q[4] = cm2;
			q[6] = cm3;
			br_aes_ct_ortho(q);
			br_aes_ct_bitslice_encrypt(ctx->num_rounds, sk_exp, q);
			br_aes_ct_ortho(q);
			cm0 = q[0];
			cm1 = q[2];
			cm2 = q[4];
			cm3 = q[6];
			break;
		}
	}

	br_enc32be(ivbuf +  0, iv0);
	br_enc32be(ivbuf +  4, iv1);
	br_enc32be(ivbuf +  8, iv2);
	br_enc32be(ivbuf + 12, iv3);
	br_enc32le((unsigned char *)cbcmac +  0, cm0);
	br_enc32le((unsigned char *)cbcmac +  4, cm1);
	br_enc32le((unsigned char *)cbcmac +  8, cm2);
	br_enc32le((unsigned char *)cbcmac + 12, cm3);
}