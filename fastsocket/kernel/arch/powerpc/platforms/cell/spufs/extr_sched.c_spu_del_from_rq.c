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
struct spu_context {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  runq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __spu_del_from_rq (struct spu_context*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* spu_prio ; 

void spu_del_from_rq(struct spu_context *ctx)
{
	spin_lock(&spu_prio->runq_lock);
	__spu_del_from_rq(ctx);
	spin_unlock(&spu_prio->runq_lock);
}