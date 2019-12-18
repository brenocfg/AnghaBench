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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  num_rounds; int /*<<< orphan*/  skey; } ;
typedef  TYPE_1__ br_aes_ct_ctr_keys ;

/* Variables and functions */
 int /*<<< orphan*/  br_aes_ct_bitslice_encrypt (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  br_aes_ct_ortho (scalar_t__*) ; 
 int /*<<< orphan*/  br_aes_ct_skey_expand (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ br_dec32le (unsigned char const*) ; 
 int /*<<< orphan*/  br_enc32le (unsigned char*,scalar_t__) ; 
 scalar_t__ br_swap32 (scalar_t__) ; 
 int /*<<< orphan*/  xorbuf (unsigned char*,unsigned char*,int) ; 

uint32_t
br_aes_ct_ctr_run(const br_aes_ct_ctr_keys *ctx,
	const void *iv, uint32_t cc, void *data, size_t len)
{
	unsigned char *buf;
	const unsigned char *ivbuf;
	uint32_t iv0, iv1, iv2;
	uint32_t sk_exp[120];

	br_aes_ct_skey_expand(sk_exp, ctx->num_rounds, ctx->skey);
	ivbuf = iv;
	iv0 = br_dec32le(ivbuf);
	iv1 = br_dec32le(ivbuf + 4);
	iv2 = br_dec32le(ivbuf + 8);
	buf = data;
	while (len > 0) {
		uint32_t q[8];
		unsigned char tmp[32];

		/*
		 * TODO: see if we can save on the first br_aes_ct_ortho()
		 * call, since iv0/iv1/iv2 are constant for the whole run.
		 */
		q[0] = q[1] = iv0;
		q[2] = q[3] = iv1;
		q[4] = q[5] = iv2;
		q[6] = br_swap32(cc);
		q[7] = br_swap32(cc + 1);
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
			cc ++;
			if (len > 16) {
				cc ++;
			}
			break;
		}
		xorbuf(buf, tmp, 32);
		buf += 32;
		len -= 32;
		cc += 2;
	}
	return cc;
}