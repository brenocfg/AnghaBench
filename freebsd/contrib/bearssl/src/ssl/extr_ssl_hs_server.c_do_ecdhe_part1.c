#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ecdhe_curve; size_t ecdhe_point_len; int* pad; int /*<<< orphan*/  ecdhe_point; int /*<<< orphan*/  server_random; int /*<<< orphan*/  client_random; TYPE_1__* iec; int /*<<< orphan*/  rng; } ;
struct TYPE_9__ {unsigned int* ecdhe_key; size_t ecdhe_key_len; unsigned int sign_hash_id; TYPE_2__ eng; TYPE_4__** policy_vtable; } ;
typedef  TYPE_3__ br_ssl_server_context ;
struct TYPE_10__ {size_t (* do_sign ) (TYPE_4__**,unsigned int,size_t*,size_t,int) ;} ;
struct TYPE_7__ {int supported_curves; unsigned char* (* order ) (int,size_t*) ;size_t (* mulgen ) (int /*<<< orphan*/ ,int*,size_t,int) ;} ;

/* Variables and functions */
 int BR_ERR_INVALID_ALGORITHM ; 
 int /*<<< orphan*/  br_hmac_drbg_generate (int /*<<< orphan*/ *,unsigned int*,size_t) ; 
 size_t hash_data (TYPE_3__*,size_t*,unsigned int,size_t*,size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 unsigned char* stub1 (int,size_t*) ; 
 size_t stub2 (int /*<<< orphan*/ ,int*,size_t,int) ; 
 size_t stub3 (TYPE_4__**,unsigned int,size_t*,size_t,int) ; 

__attribute__((used)) static int
do_ecdhe_part1(br_ssl_server_context *ctx, int curve)
{
	unsigned algo_id;
	unsigned mask;
	const unsigned char *order;
	size_t olen, glen;
	size_t hv_len, sig_len;

	if (!((ctx->eng.iec->supported_curves >> curve) & 1)) {
		return -BR_ERR_INVALID_ALGORITHM;
	}
	ctx->eng.ecdhe_curve = curve;

	/*
	 * Generate our private key. We need a non-zero random value
	 * which is lower than the curve order, in a "large enough"
	 * range. We force the top bit to 0 and bottom bit to 1, which
	 * does the trick. Note that contrary to what happens in ECDSA,
	 * this is not a problem if we do not cover the full range of
	 * possible values.
	 */
	order = ctx->eng.iec->order(curve, &olen);
	mask = 0xFF;
	while (mask >= order[0]) {
		mask >>= 1;
	}
	br_hmac_drbg_generate(&ctx->eng.rng, ctx->ecdhe_key, olen);
	ctx->ecdhe_key[0] &= mask;
	ctx->ecdhe_key[olen - 1] |= 0x01;
	ctx->ecdhe_key_len = olen;

	/*
	 * Compute our ECDH point.
	 */
	glen = ctx->eng.iec->mulgen(ctx->eng.ecdhe_point,
		ctx->ecdhe_key, olen, curve);
	ctx->eng.ecdhe_point_len = glen;

	/*
	 * Assemble the message to be signed, and possibly hash it.
	 */
	memcpy(ctx->eng.pad, ctx->eng.client_random, 32);
	memcpy(ctx->eng.pad + 32, ctx->eng.server_random, 32);
	ctx->eng.pad[64 + 0] = 0x03;
	ctx->eng.pad[64 + 1] = 0x00;
	ctx->eng.pad[64 + 2] = curve;
	ctx->eng.pad[64 + 3] = ctx->eng.ecdhe_point_len;
	memcpy(ctx->eng.pad + 64 + 4,
		ctx->eng.ecdhe_point, ctx->eng.ecdhe_point_len);
	hv_len = 64 + 4 + ctx->eng.ecdhe_point_len;
	algo_id = ctx->sign_hash_id;
	if (algo_id >= (unsigned)0xFF00) {
		hv_len = hash_data(ctx, ctx->eng.pad, algo_id & 0xFF,
			ctx->eng.pad, hv_len);
		if (hv_len == 0) {
			return -BR_ERR_INVALID_ALGORITHM;
		}
	}

	sig_len = (*ctx->policy_vtable)->do_sign(ctx->policy_vtable,
		algo_id, ctx->eng.pad, hv_len, sizeof ctx->eng.pad);
	return sig_len ? (int)sig_len : -BR_ERR_INVALID_ALGORITHM;
}