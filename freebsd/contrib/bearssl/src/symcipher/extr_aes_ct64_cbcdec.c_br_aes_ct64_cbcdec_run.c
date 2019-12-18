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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  num_rounds; int /*<<< orphan*/  skey; } ;
typedef  TYPE_1__ br_aes_ct64_cbcdec_keys ;

/* Variables and functions */
 int /*<<< orphan*/  br_aes_ct64_bitslice_decrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_aes_ct64_interleave_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_aes_ct64_interleave_out (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_aes_ct64_ortho (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_aes_ct64_skey_expand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_range_dec32le (int /*<<< orphan*/ *,size_t,unsigned char*) ; 
 int /*<<< orphan*/  br_range_enc32le (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
br_aes_ct64_cbcdec_run(const br_aes_ct64_cbcdec_keys *ctx,
	void *iv, void *data, size_t len)
{
	unsigned char *buf;
	uint64_t sk_exp[120];
	uint32_t ivw[4];

	br_aes_ct64_skey_expand(sk_exp, ctx->num_rounds, ctx->skey);
	br_range_dec32le(ivw, 4, iv);
	buf = data;
	while (len > 0) {
		uint64_t q[8];
		uint32_t w1[16], w2[16];
		int i;

		if (len >= 64) {
			br_range_dec32le(w1, 16, buf);
		} else {
			br_range_dec32le(w1, len >> 2, buf);
		}
		for (i = 0; i < 4; i ++) {
			br_aes_ct64_interleave_in(
				&q[i], &q[i + 4], w1 + (i << 2));
		}
		br_aes_ct64_ortho(q);
		br_aes_ct64_bitslice_decrypt(ctx->num_rounds, sk_exp, q);
		br_aes_ct64_ortho(q);
		for (i = 0; i < 4; i ++) {
			br_aes_ct64_interleave_out(
				w2 + (i << 2), q[i], q[i + 4]);
		}
		for (i = 0; i < 4; i ++) {
			w2[i] ^= ivw[i];
		}
		if (len >= 64) {
			for (i = 4; i < 16; i ++) {
				w2[i] ^= w1[i - 4];
			}
			memcpy(ivw, w1 + 12, sizeof ivw);
			br_range_enc32le(buf, w2, 16);
		} else {
			int j;

			j = (int)(len >> 2);
			for (i = 4; i < j; i ++) {
				w2[i] ^= w1[i - 4];
			}
			memcpy(ivw, w1 + j - 4, sizeof ivw);
			br_range_enc32le(buf, w2, j);
			break;
		}
		buf += 64;
		len -= 64;
	}
	br_range_enc32le(iv, ivw, 4);
}