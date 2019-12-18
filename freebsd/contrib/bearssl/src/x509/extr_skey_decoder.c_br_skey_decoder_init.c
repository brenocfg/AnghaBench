#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * rp; int /*<<< orphan*/ * dp; } ;
struct TYPE_6__ {TYPE_3__ cpu; int /*<<< orphan*/ * rp_stack; int /*<<< orphan*/ * dp_stack; } ;
typedef  TYPE_1__ br_skey_decoder_context ;

/* Variables and functions */
 int /*<<< orphan*/  br_skey_decoder_init_main (TYPE_3__*) ; 
 int /*<<< orphan*/  br_skey_decoder_run (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
br_skey_decoder_init(br_skey_decoder_context *ctx)
{
	memset(ctx, 0, sizeof *ctx);
	ctx->cpu.dp = &ctx->dp_stack[0];
	ctx->cpu.rp = &ctx->rp_stack[0];
	br_skey_decoder_init_main(&ctx->cpu);
	br_skey_decoder_run(&ctx->cpu);
}