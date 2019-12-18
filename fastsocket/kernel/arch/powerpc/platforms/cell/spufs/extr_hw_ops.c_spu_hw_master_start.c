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
typedef  int u64 ;
struct spu_context {struct spu* spu; } ;
struct spu {int /*<<< orphan*/  register_lock; } ;

/* Variables and functions */
 int MFC_STATE1_MASTER_RUN_CONTROL_MASK ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int spu_mfc_sr1_get (struct spu*) ; 
 int /*<<< orphan*/  spu_mfc_sr1_set (struct spu*,int) ; 

__attribute__((used)) static void spu_hw_master_start(struct spu_context *ctx)
{
	struct spu *spu = ctx->spu;
	u64 sr1;

	spin_lock_irq(&spu->register_lock);
	sr1 = spu_mfc_sr1_get(spu) | MFC_STATE1_MASTER_RUN_CONTROL_MASK;
	spu_mfc_sr1_set(spu, sr1);
	spin_unlock_irq(&spu->register_lock);
}