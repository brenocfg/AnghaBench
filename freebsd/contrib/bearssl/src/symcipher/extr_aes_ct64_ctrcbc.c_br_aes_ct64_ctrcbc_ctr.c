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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  num_rounds; int /*<<< orphan*/  skey; } ;
typedef  TYPE_1__ br_aes_ct64_ctrcbc_keys ;

/* Variables and functions */
 int /*<<< orphan*/  br_aes_ct64_bitslice_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_aes_ct64_interleave_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  br_aes_ct64_interleave_out (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_aes_ct64_ortho (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_aes_ct64_skey_expand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int br_dec32be (unsigned char*) ; 
 int /*<<< orphan*/  br_enc32be (unsigned char*,int) ; 
 int /*<<< orphan*/  br_range_enc32le (unsigned char*,int*,int) ; 
 int br_swap32 (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xorbuf (unsigned char*,unsigned char*,int) ; 

void
br_aes_ct64_ctrcbc_ctr(const br_aes_ct64_ctrcbc_keys *ctx,
	void *ctr, void *data, size_t len)
{
	unsigned char *buf;
	unsigned char *ivbuf;
	uint32_t iv0, iv1, iv2, iv3;
	uint64_t sk_exp[120];

	br_aes_ct64_skey_expand(sk_exp, ctx->num_rounds, ctx->skey);

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
		uint64_t q[8];
		uint32_t w[16];
		unsigned char tmp[64];
		int i, j;

		/*
		 * The bitslice implementation expects values in
		 * little-endian convention, so we have to byteswap them.
		 */
		j = (len >= 64) ? 16 : (int)(len >> 2);
		for (i = 0; i < j; i += 4) {
			uint32_t carry;

			w[i + 0] = br_swap32(iv0);
			w[i + 1] = br_swap32(iv1);
			w[i + 2] = br_swap32(iv2);
			w[i + 3] = br_swap32(iv3);
			iv3 ++;
			carry = ~(iv3 | -iv3) >> 31;
			iv2 += carry;
			carry &= -(~(iv2 | -iv2) >> 31);
			iv1 += carry;
			carry &= -(~(iv1 | -iv1) >> 31);
			iv0 += carry;
		}
		memset(w + i, 0, (16 - i) * sizeof(uint32_t));

		for (i = 0; i < 4; i ++) {
			br_aes_ct64_interleave_in(
				&q[i], &q[i + 4], w + (i << 2));
		}
		br_aes_ct64_ortho(q);
		br_aes_ct64_bitslice_encrypt(ctx->num_rounds, sk_exp, q);
		br_aes_ct64_ortho(q);
		for (i = 0; i < 4; i ++) {
			br_aes_ct64_interleave_out(
				w + (i << 2), q[i], q[i + 4]);
		}

		br_range_enc32le(tmp, w, 16);
		if (len <= 64) {
			xorbuf(buf, tmp, len);
			break;
		}
		xorbuf(buf, tmp, 64);
		buf += 64;
		len -= 64;
	}
	br_enc32be(ivbuf +  0, iv0);
	br_enc32be(ivbuf +  4, iv1);
	br_enc32be(ivbuf +  8, iv2);
	br_enc32be(ivbuf + 12, iv3);
}