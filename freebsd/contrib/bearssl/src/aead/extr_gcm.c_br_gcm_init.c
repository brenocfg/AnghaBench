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
typedef  int /*<<< orphan*/  br_ghash ;
struct TYPE_6__ {unsigned char* h; int /*<<< orphan*/  gh; TYPE_2__ const** bctx; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_1__ br_gcm_context ;
struct TYPE_7__ {int /*<<< orphan*/  (* run ) (TYPE_2__ const**,unsigned char*,int /*<<< orphan*/ ,unsigned char*,int) ;} ;
typedef  TYPE_2__ br_block_ctr_class ;

/* Variables and functions */
 int /*<<< orphan*/  br_gcm_vtable ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const**,unsigned char*,int /*<<< orphan*/ ,unsigned char*,int) ; 

void
br_gcm_init(br_gcm_context *ctx, const br_block_ctr_class **bctx, br_ghash gh)
{
	unsigned char iv[12];

	ctx->vtable = &br_gcm_vtable;
	ctx->bctx = bctx;
	ctx->gh = gh;

	/*
	 * The GHASH key h[] is the raw encryption of the all-zero
	 * block. Since we only have a CTR implementation, we use it
	 * with an all-zero IV and a zero counter, to CTR-encrypt an
	 * all-zero block.
	 */
	memset(ctx->h, 0, sizeof ctx->h);
	memset(iv, 0, sizeof iv);
	(*bctx)->run(bctx, iv, 0, ctx->h, sizeof ctx->h);
}