#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int iv0; int iv1; int iv2; int iv3; } ;
union dynamic_sa_contents {TYPE_1__ bf; int /*<<< orphan*/  w; } ;
typedef  int u32 ;
struct dynamic_sa_ctl {int /*<<< orphan*/  sa_contents; } ;
struct crypto4xx_ctx {scalar_t__ direction; scalar_t__ sa_out; scalar_t__ sa_in; } ;

/* Variables and functions */
 scalar_t__ DIR_INBOUND ; 

u32 get_dynamic_sa_iv_size(struct crypto4xx_ctx *ctx)
{
	union dynamic_sa_contents cts;

	if (ctx->direction == DIR_INBOUND)
		cts.w = ((struct dynamic_sa_ctl *) ctx->sa_in)->sa_contents;
	else
		cts.w = ((struct dynamic_sa_ctl *) ctx->sa_out)->sa_contents;
	return (cts.bf.iv0 + cts.bf.iv1 + cts.bf.iv2 + cts.bf.iv3) * 4;
}