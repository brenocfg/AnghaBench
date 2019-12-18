#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned char* L2; unsigned char* L4; TYPE_2__ const** bctx; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ br_eax_context ;
struct TYPE_7__ {int /*<<< orphan*/  (* ctr ) (TYPE_2__ const**,unsigned char*,unsigned char*,int) ;} ;
typedef  TYPE_2__ br_block_ctrcbc_class ;

/* Variables and functions */
 int /*<<< orphan*/  br_eax_vtable ; 
 int /*<<< orphan*/  double_gf128 (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const**,unsigned char*,unsigned char*,int) ; 

void
br_eax_init(br_eax_context *ctx, const br_block_ctrcbc_class **bctx)
{
	unsigned char tmp[16], iv[16];

	ctx->vtable = &br_eax_vtable;
	ctx->bctx = bctx;

	/*
	 * Encrypt a whole-zero block to compute L2 and L4.
	 */
	memset(tmp, 0, sizeof tmp);
	memset(iv, 0, sizeof iv);
	(*bctx)->ctr(bctx, iv, tmp, sizeof tmp);
	double_gf128(ctx->L2, tmp);
	double_gf128(ctx->L4, ctx->L2);
}