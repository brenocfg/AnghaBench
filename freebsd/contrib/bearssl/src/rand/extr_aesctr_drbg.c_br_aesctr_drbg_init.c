#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ *,unsigned char*,int) ;} ;
typedef  TYPE_2__ br_block_ctr_class ;
struct TYPE_7__ {int /*<<< orphan*/  vtable; } ;
struct TYPE_9__ {scalar_t__ cc; TYPE_1__ sk; int /*<<< orphan*/ * vtable; } ;
typedef  TYPE_3__ br_aesctr_drbg_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_aesctr_drbg_update (TYPE_3__*,void const*,size_t) ; 
 int /*<<< orphan*/  br_aesctr_drbg_vtable ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,unsigned char*,int) ; 

void
br_aesctr_drbg_init(br_aesctr_drbg_context *ctx,
	const br_block_ctr_class *aesctr,
	const void *seed, size_t len)
{
	unsigned char tmp[16];

	ctx->vtable = &br_aesctr_drbg_vtable;
	memset(tmp, 0, sizeof tmp);
	aesctr->init(&ctx->sk.vtable, tmp, 16);
	ctx->cc = 0;
	br_aesctr_drbg_update(ctx, seed, len);
}