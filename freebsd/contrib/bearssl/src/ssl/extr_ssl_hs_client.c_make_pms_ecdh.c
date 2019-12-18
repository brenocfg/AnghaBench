#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {int curve; unsigned char* q; size_t qlen; } ;
struct TYPE_13__ {TYPE_1__ ec; } ;
struct TYPE_15__ {TYPE_2__ key; } ;
typedef  TYPE_4__ br_x509_pkey ;
struct TYPE_16__ {TYPE_4__* (* get_pkey ) (TYPE_5__ const**,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_5__ br_x509_class ;
struct TYPE_11__ {int ecdhe_curve; unsigned char* ecdhe_point; size_t ecdhe_point_len; unsigned char* pad; TYPE_3__* iec; int /*<<< orphan*/  rng; TYPE_5__** x509ctx; } ;
struct TYPE_17__ {TYPE_10__ eng; } ;
typedef  TYPE_6__ br_ssl_client_context ;
struct TYPE_14__ {int supported_curves; unsigned char* (* order ) (int,size_t*) ;size_t (* xoff ) (int,size_t*) ;int /*<<< orphan*/  (* mulgen ) (unsigned char*,unsigned char*,size_t,int) ;int /*<<< orphan*/  (* mul ) (unsigned char*,size_t,unsigned char*,size_t,int) ;int /*<<< orphan*/  (* generator ) (int,size_t*) ;} ;

/* Variables and functions */
 int BR_ERR_INVALID_ALGORITHM ; 
 int /*<<< orphan*/  br_hmac_drbg_generate (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  br_ssl_engine_compute_master (TYPE_10__*,int,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 TYPE_4__* stub1 (TYPE_5__ const**,int /*<<< orphan*/ *) ; 
 unsigned char* stub2 (int,size_t*) ; 
 int /*<<< orphan*/  stub3 (int,size_t*) ; 
 int /*<<< orphan*/  stub4 (unsigned char*,size_t,unsigned char*,size_t,int) ; 
 size_t stub5 (int,size_t*) ; 
 int /*<<< orphan*/  stub6 (unsigned char*,unsigned char*,size_t,int) ; 

__attribute__((used)) static int
make_pms_ecdh(br_ssl_client_context *ctx, unsigned ecdhe, int prf_id)
{
	int curve;
	unsigned char key[66], point[133];
	const unsigned char *order, *point_src;
	size_t glen, olen, point_len, xoff, xlen;
	unsigned char mask;

	if (ecdhe) {
		curve = ctx->eng.ecdhe_curve;
		point_src = ctx->eng.ecdhe_point;
		point_len = ctx->eng.ecdhe_point_len;
	} else {
		const br_x509_class **xc;
		const br_x509_pkey *pk;

		xc = ctx->eng.x509ctx;
		pk = (*xc)->get_pkey(xc, NULL);
		curve = pk->key.ec.curve;
		point_src = pk->key.ec.q;
		point_len = pk->key.ec.qlen;
	}
	if ((ctx->eng.iec->supported_curves & ((uint32_t)1 << curve)) == 0) {
		return -BR_ERR_INVALID_ALGORITHM;
	}

	/*
	 * We need to generate our key, as a non-zero random value which
	 * is lower than the curve order, in a "large enough" range. We
	 * force top bit to 0 and bottom bit to 1, which guarantees that
	 * the value is in the proper range.
	 */
	order = ctx->eng.iec->order(curve, &olen);
	mask = 0xFF;
	while (mask >= order[0]) {
		mask >>= 1;
	}
	br_hmac_drbg_generate(&ctx->eng.rng, key, olen);
	key[0] &= mask;
	key[olen - 1] |= 0x01;

	/*
	 * Compute the common ECDH point, whose X coordinate is the
	 * pre-master secret.
	 */
	ctx->eng.iec->generator(curve, &glen);
	if (glen != point_len) {
		return -BR_ERR_INVALID_ALGORITHM;
	}

	memcpy(point, point_src, glen);
	if (!ctx->eng.iec->mul(point, glen, key, olen, curve)) {
		return -BR_ERR_INVALID_ALGORITHM;
	}

	/*
	 * The pre-master secret is the X coordinate.
	 */
	xoff = ctx->eng.iec->xoff(curve, &xlen);
	br_ssl_engine_compute_master(&ctx->eng, prf_id, point + xoff, xlen);

	ctx->eng.iec->mulgen(point, key, olen, curve);
	memcpy(ctx->eng.pad, point, glen);
	return (int)glen;
}