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
struct TYPE_2__ {int /*<<< orphan*/  int_mask_class2_RW; int /*<<< orphan*/  int_mask_class1_RW; int /*<<< orphan*/  int_mask_class0_RW; } ;
struct spu_state {TYPE_1__ priv1; } ;
struct spu {int /*<<< orphan*/  register_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spu_int_mask_set (struct spu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void reenable_interrupts(struct spu_state *csa, struct spu *spu)
{
	/* Restore, Step 75:
	 *     Re-enable SPU interrupts.
	 */
	spin_lock_irq(&spu->register_lock);
	spu_int_mask_set(spu, 0, csa->priv1.int_mask_class0_RW);
	spu_int_mask_set(spu, 1, csa->priv1.int_mask_class1_RW);
	spu_int_mask_set(spu, 2, csa->priv1.int_mask_class2_RW);
	spin_unlock_irq(&spu->register_lock);
}