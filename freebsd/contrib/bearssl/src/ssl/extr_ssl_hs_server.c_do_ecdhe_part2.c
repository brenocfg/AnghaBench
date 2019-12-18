#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int ecdhe_curve; TYPE_2__* iec; } ;
struct TYPE_8__ {int /*<<< orphan*/  ecdhe_key_len; int /*<<< orphan*/  ecdhe_key; TYPE_1__ eng; } ;
typedef  TYPE_3__ br_ssl_server_context ;
struct TYPE_7__ {size_t (* xoff ) (int,size_t*) ;int /*<<< orphan*/  (* mul ) (unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ecdh_common (TYPE_3__*,int,unsigned char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (unsigned char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t stub2 (int,size_t*) ; 

__attribute__((used)) static void
do_ecdhe_part2(br_ssl_server_context *ctx, int prf_id,
	unsigned char *cpoint, size_t cpoint_len)
{
	int curve;
	uint32_t ctl;
	size_t xoff, xlen;

	curve = ctx->eng.ecdhe_curve;

	/*
	 * Finalise the key exchange.
	 */
	ctl = ctx->eng.iec->mul(cpoint, cpoint_len,
		ctx->ecdhe_key, ctx->ecdhe_key_len, curve);
	xoff = ctx->eng.iec->xoff(curve, &xlen);
	ecdh_common(ctx, prf_id, cpoint + xoff, xlen, ctl);

	/*
	 * Clear the ECDHE private key. Forward Secrecy is achieved insofar
	 * as that key does not get stolen, so we'd better destroy it
	 * as soon as it ceases to be useful.
	 */
	memset(ctx->ecdhe_key, 0, ctx->ecdhe_key_len);
}