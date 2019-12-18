#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long long slb_flt; scalar_t__ slb_flt_base; } ;
struct spu_context {scalar_t__ state; TYPE_3__ stats; TYPE_2__* spu; } ;
struct TYPE_4__ {scalar_t__ slb_flt; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ SPU_STATE_RUNNABLE ; 

__attribute__((used)) static unsigned long long spufs_slb_flts(struct spu_context *ctx)
{
	unsigned long long slb_flts = ctx->stats.slb_flt;

	if (ctx->state == SPU_STATE_RUNNABLE) {
		slb_flts += (ctx->spu->stats.slb_flt -
			     ctx->stats.slb_flt_base);
	}

	return slb_flts;
}