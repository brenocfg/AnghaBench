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
typedef  scalar_t__ u64 ;
struct ehca_shca {int /*<<< orphan*/  ib_device; int /*<<< orphan*/  ipz_hca_handle; } ;
struct ehca_eq {int /*<<< orphan*/  ipz_queue; int /*<<< orphan*/  interrupt_task; scalar_t__ is_initialized; int /*<<< orphan*/  ist; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ H_SUCCESS ; 
 int /*<<< orphan*/  ehca_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ hipz_h_destroy_eq (int /*<<< orphan*/ ,struct ehca_eq*) ; 
 int /*<<< orphan*/  ibmebus_free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ipz_queue_dtor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shca_list_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

int ehca_destroy_eq(struct ehca_shca *shca, struct ehca_eq *eq)
{
	unsigned long flags;
	u64 h_ret;

	ibmebus_free_irq(eq->ist, (void *)shca);

	spin_lock_irqsave(&shca_list_lock, flags);
	eq->is_initialized = 0;
	spin_unlock_irqrestore(&shca_list_lock, flags);

	tasklet_kill(&eq->interrupt_task);

	h_ret = hipz_h_destroy_eq(shca->ipz_hca_handle, eq);

	if (h_ret != H_SUCCESS) {
		ehca_err(&shca->ib_device, "Can't free EQ resources.");
		return -EINVAL;
	}
	ipz_queue_dtor(NULL, &eq->ipz_queue);

	return 0;
}