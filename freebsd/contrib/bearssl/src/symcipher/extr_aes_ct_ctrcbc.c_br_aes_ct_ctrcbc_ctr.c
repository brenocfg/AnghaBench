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
 int /*<<< orphan*/  br_enc32be (unsigned char*,int) ; 
 int /*<<< orphan*/  br_enc32le (unsigned char*,int) ; 
 int br_swap32 (int) ; 
 int /*<<< orphan*/  xorbuf (unsigned char*,unsigned char*,int) ; 

void
br_aes_ct_ctrcbc_ctr(const br_aes_ct_ctrcbc_keys *ctx,
	void *ctr, void *data, size_t len)
{
	unsigned char *buf;
	unsigned char *ivbuf;
	uint32_t iv0, iv1, iv2, iv3;
	uint32_t sk_exp[120];

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

	buf = data;
	while (len > 0) {
		uint32_t q[8], carry;
		unsigned char tmp[32];

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
		q[1] = br_swap32(iv0);
		q[3] = br_swap32(iv1);
		q[5] = br_swap32(iv2);
		q[7] = br_swap32(iv3);
		if (len > 16) {
			iv3 ++;
			carry = ~(iv3 | -iv3) >> 31;
			iv2 += carry;
			carry &= -(~(iv2 | -iv2) >> 31);
			iv1 += carry;
			carry &= -(~(iv1 | -iv1) >> 31);
			iv0 += carry;
		}

		br_aes_ct_ortho(q);
		br_aes_ct_bitslice_encrypt(ctx->num_rounds, sk_exp, q);
		br_aes_ct_ortho(q);

		br_enc32le(tmp, q[0]);
		br_enc32le(tmp + 4, q[2]);
		br_enc32le(tmp + 8, q[4]);
		br_enc32le(tmp + 12, q[6]);
		br_enc32le(tmp + 16, q[1]);
		br_enc32le(tmp + 20, q[3]);
		br_enc32le(tmp + 24, q[5]);
		br_enc32le(tmp + 28, q[7]);

		if (len <= 32) {
			xorbuf(buf, tmp, len);
			break;
		}
		xorbuf(buf, tmp, 32);
		buf += 32;
		len -= 32;
	}
	br_enc32be(ivbuf +  0, iv0);
	br_enc32be(ivbuf +  4, iv1);
	br_enc32be(ivbuf +  8, iv2);
	br_enc32be(ivbuf + 12, iv3);
}