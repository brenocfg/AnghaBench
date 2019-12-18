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
struct spu_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PRIO ; 
 int /*<<< orphan*/  __spu_deactivate (struct spu_context*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_context_nospu_trace (int /*<<< orphan*/ ,struct spu_context*) ; 
 int /*<<< orphan*/  spu_deactivate__enter ; 

void spu_deactivate(struct spu_context *ctx)
{
	spu_context_nospu_trace(spu_deactivate__enter, ctx);
	__spu_deactivate(ctx, 1, MAX_PRIO);
}