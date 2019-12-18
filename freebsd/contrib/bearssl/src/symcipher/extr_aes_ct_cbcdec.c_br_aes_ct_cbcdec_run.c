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
typedef  TYPE_1__ br_aes_ct_cbcdec_keys ;

/* Variables and functions */
 int /*<<< orphan*/  br_aes_ct_bitslice_decrypt (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  br_aes_ct_ortho (int*) ; 
 int /*<<< orphan*/  br_aes_ct_skey_expand (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int br_dec32le (unsigned char*) ; 
 int /*<<< orphan*/  br_enc32le (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

void
br_aes_ct_cbcdec_run(const br_aes_ct_cbcdec_keys *ctx,
	void *iv, void *data, size_t len)
{
	unsigned char *buf, *ivbuf;
	uint32_t iv0, iv1, iv2, iv3;
	uint32_t sk_exp[120];

	br_aes_ct_skey_expand(sk_exp, ctx->num_rounds, ctx->skey);
	ivbuf = iv;
	iv0 = br_dec32le(ivbuf);
	iv1 = br_dec32le(ivbuf + 4);
	iv2 = br_dec32le(ivbuf + 8);
	iv3 = br_dec32le(ivbuf + 12);
	buf = data;
	while (len > 0) {
		uint32_t q[8], sq[8];

		q[0] = br_dec32le(buf);
		q[2] = br_dec32le(buf + 4);
		q[4] = br_dec32le(buf + 8);
		q[6] = br_dec32le(buf + 12);
		if (len >= 32) {
			q[1] = br_dec32le(buf + 16);
			q[3] = br_dec32le(buf + 20);
			q[5] = br_dec32le(buf + 24);
			q[7] = br_dec32le(buf + 28);
		} else {
			q[1] = 0;
			q[3] = 0;
			q[5] = 0;
			q[7] = 0;
		}
		memcpy(sq, q, sizeof q);
		br_aes_ct_ortho(q);
		br_aes_ct_bitslice_decrypt(ctx->num_rounds, sk_exp, q);
		br_aes_ct_ortho(q);
		br_enc32le(buf, q[0] ^ iv0);
		br_enc32le(buf + 4, q[2] ^ iv1);
		br_enc32le(buf + 8, q[4] ^ iv2);
		br_enc32le(buf + 12, q[6] ^ iv3);
		if (len < 32) {
			iv0 = sq[0];
			iv1 = sq[2];
			iv2 = sq[4];
			iv3 = sq[6];
			break;
		}
		br_enc32le(buf + 16, q[1] ^ sq[0]);
		br_enc32le(buf + 20, q[3] ^ sq[2]);
		br_enc32le(buf + 24, q[5] ^ sq[4]);
		br_enc32le(buf + 28, q[7] ^ sq[6]);
		iv0 = sq[1];
		iv1 = sq[3];
		iv2 = sq[5];
		iv3 = sq[7];
		buf += 32;
		len -= 32;
	}
	br_enc32le(ivbuf, iv0);
	br_enc32le(ivbuf + 4, iv1);
	br_enc32le(ivbuf + 8, iv2);
	br_enc32le(ivbuf + 12, iv3);
}