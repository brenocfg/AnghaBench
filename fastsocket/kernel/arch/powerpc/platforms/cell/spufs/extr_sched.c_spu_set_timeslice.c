#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct spu_context {scalar_t__ prio; void* time_slice; } ;

/* Variables and functions */
 int DEF_SPU_TIMESLICE ; 
 scalar_t__ NORMAL_PRIO ; 
 void* SCALE_PRIO (int,scalar_t__) ; 

void spu_set_timeslice(struct spu_context *ctx)
{
	if (ctx->prio < NORMAL_PRIO)
		ctx->time_slice = SCALE_PRIO(DEF_SPU_TIMESLICE * 4, ctx->prio);
	else
		ctx->time_slice = SCALE_PRIO(DEF_SPU_TIMESLICE, ctx->prio);
}