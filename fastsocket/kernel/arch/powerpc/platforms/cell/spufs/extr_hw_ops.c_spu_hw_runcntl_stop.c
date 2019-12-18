#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spu_context {TYPE_2__* spu; } ;
struct TYPE_4__ {int /*<<< orphan*/  register_lock; TYPE_1__* problem; } ;
struct TYPE_3__ {int /*<<< orphan*/  spu_status_R; int /*<<< orphan*/  spu_runcntl_RW; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPU_RUNCNTL_STOP ; 
 int SPU_STATUS_RUNNING ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spu_hw_runcntl_stop(struct spu_context *ctx)
{
	spin_lock_irq(&ctx->spu->register_lock);
	out_be32(&ctx->spu->problem->spu_runcntl_RW, SPU_RUNCNTL_STOP);
	while (in_be32(&ctx->spu->problem->spu_status_R) & SPU_STATUS_RUNNING)
		cpu_relax();
	spin_unlock_irq(&ctx->spu->register_lock);
}