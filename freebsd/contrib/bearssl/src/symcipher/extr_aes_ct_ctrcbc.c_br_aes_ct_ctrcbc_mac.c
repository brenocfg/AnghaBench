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
 int br_dec32le (unsigned char const*) ; 
 int /*<<< orphan*/  br_enc32le (unsigned char*,int) ; 

void
br_aes_ct_ctrcbc_mac(const br_aes_ct_ctrcbc_keys *ctx,
	void *cbcmac, const void *data, size_t len)
{
	const unsigned char *buf;
	uint32_t cm0, cm1, cm2, cm3;
	uint32_t q[8];
	uint32_t sk_exp[120];

	br_aes_ct_skey_expand(sk_exp, ctx->num_rounds, ctx->skey);

	buf = data;
	cm0 = br_dec32le((unsigned char *)cbcmac +  0);
	cm1 = br_dec32le((unsigned char *)cbcmac +  4);
	cm2 = br_dec32le((unsigned char *)cbcmac +  8);
	cm3 = br_dec32le((unsigned char *)cbcmac + 12);
	q[1] = 0;
	q[3] = 0;
	q[5] = 0;
	q[7] = 0;

	while (len > 0) {
		q[0] = cm0 ^ br_dec32le(buf +  0);
		q[2] = cm1 ^ br_dec32le(buf +  4);
		q[4] = cm2 ^ br_dec32le(buf +  8);
		q[6] = cm3 ^ br_dec32le(buf + 12);

		br_aes_ct_ortho(q);
		br_aes_ct_bitslice_encrypt(ctx->num_rounds, sk_exp, q);
		br_aes_ct_ortho(q);

		cm0 = q[0];
		cm1 = q[2];
		cm2 = q[4];
		cm3 = q[6];
		buf += 16;
		len -= 16;
	}

	br_enc32le((unsigned char *)cbcmac +  0, cm0);
	br_enc32le((unsigned char *)cbcmac +  4, cm1);
	br_enc32le((unsigned char *)cbcmac +  8, cm2);
	br_enc32le((unsigned char *)cbcmac + 12, cm3);
}