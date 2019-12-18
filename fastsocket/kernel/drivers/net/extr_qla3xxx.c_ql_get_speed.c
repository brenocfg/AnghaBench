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
typedef  int /*<<< orphan*/  u32 ;
struct ql3_adapter {int mac_index; int /*<<< orphan*/  hw_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_PHY_GIO_SEM_MASK ; 
 int QL_RESOURCE_BITS_BASE_CODE ; 
 int /*<<< orphan*/  ql_get_link_speed (struct ql3_adapter*) ; 
 scalar_t__ ql_sem_spinlock (struct ql3_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_sem_unlock (struct ql3_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u32 ql_get_speed(struct ql3_adapter *qdev)
{
	u32 status;
	unsigned long hw_flags;
	spin_lock_irqsave(&qdev->hw_lock, hw_flags);
	if(ql_sem_spinlock(qdev, QL_PHY_GIO_SEM_MASK,
		(QL_RESOURCE_BITS_BASE_CODE | (qdev->mac_index) *
			 2) << 7)) {
		spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
		return 0;
	}
	status = ql_get_link_speed(qdev);
	ql_sem_unlock(qdev, QL_PHY_GIO_SEM_MASK);
	spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
	return status;
}