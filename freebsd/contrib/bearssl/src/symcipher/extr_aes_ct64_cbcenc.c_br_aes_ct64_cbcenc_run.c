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
typedef  TYPE_1__ br_aes_ct64_cbcenc_keys ;

/* Variables and functions */
 int /*<<< orphan*/  br_aes_ct64_bitslice_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_aes_ct64_interleave_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  br_aes_ct64_interleave_out (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_aes_ct64_ortho (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  br_aes_ct64_skey_expand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int br_dec32le (unsigned char*) ; 
 int /*<<< orphan*/  br_enc32le (unsigned char*,int) ; 
 int /*<<< orphan*/  br_range_dec32le (int*,int,void*) ; 
 int /*<<< orphan*/  br_range_enc32le (void*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

void
br_aes_ct64_cbcenc_run(const br_aes_ct64_cbcenc_keys *ctx,
	void *iv, void *data, size_t len)
{
	unsigned char *buf;
	uint64_t sk_exp[120];
	uint32_t ivw[4];

	br_aes_ct64_skey_expand(sk_exp, ctx->num_rounds, ctx->skey);
	br_range_dec32le(ivw, 4, iv);
	buf = data;
	while (len > 0) {
		uint32_t w[4];
		uint64_t q[8];

		w[0] = ivw[0] ^ br_dec32le(buf);
		w[1] = ivw[1] ^ br_dec32le(buf + 4);
		w[2] = ivw[2] ^ br_dec32le(buf + 8);
		w[3] = ivw[3] ^ br_dec32le(buf + 12);
		br_aes_ct64_interleave_in(&q[0], &q[4], w);
		br_aes_ct64_ortho(q);
		br_aes_ct64_bitslice_encrypt(ctx->num_rounds, sk_exp, q);
		br_aes_ct64_ortho(q);
		br_aes_ct64_interleave_out(w, q[0], q[4]);
		memcpy(ivw, w, sizeof w);
		br_enc32le(buf, w[0]);
		br_enc32le(buf + 4, w[1]);
		br_enc32le(buf + 8, w[2]);
		br_enc32le(buf + 12, w[3]);
		buf += 16;
		len -= 16;
	}
	br_range_enc32le(iv, ivw, 4);
}