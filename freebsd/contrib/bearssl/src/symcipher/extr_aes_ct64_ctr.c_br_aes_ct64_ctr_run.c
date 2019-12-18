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
typedef  TYPE_1__ br_aes_ct64_ctr_keys ;

/* Variables and functions */
 int /*<<< orphan*/  br_aes_ct64_bitslice_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_aes_ct64_interleave_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  br_aes_ct64_interleave_out (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_aes_ct64_ortho (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_aes_ct64_skey_expand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_range_dec32le (int*,int,void const*) ; 
 int /*<<< orphan*/  br_range_enc32le (unsigned char*,int*,int) ; 
 int br_swap32 (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  xorbuf (unsigned char*,unsigned char*,int) ; 

uint32_t
br_aes_ct64_ctr_run(const br_aes_ct64_ctr_keys *ctx,
	const void *iv, uint32_t cc, void *data, size_t len)
{
	unsigned char *buf;
	uint32_t ivw[16];
	uint64_t sk_exp[120];

	br_aes_ct64_skey_expand(sk_exp, ctx->num_rounds, ctx->skey);
	br_range_dec32le(ivw, 3, iv);
	memcpy(ivw + 4, ivw, 3 * sizeof(uint32_t));
	memcpy(ivw + 8, ivw, 3 * sizeof(uint32_t));
	memcpy(ivw + 12, ivw, 3 * sizeof(uint32_t));
	buf = data;
	while (len > 0) {
		uint64_t q[8];
		uint32_t w[16];
		unsigned char tmp[64];
		int i;

		/*
		 * TODO: see if we can save on the first br_aes_ct64_ortho()
		 * call, since iv0/iv1/iv2 are constant for the whole run.
		 */
		memcpy(w, ivw, sizeof ivw);
		w[3] = br_swap32(cc);
		w[7] = br_swap32(cc + 1);
		w[11] = br_swap32(cc + 2);
		w[15] = br_swap32(cc + 3);
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
			cc += (uint32_t)len >> 4;
			break;
		}
		xorbuf(buf, tmp, 64);
		buf += 64;
		len -= 64;
		cc += 4;
	}
	return cc;
}