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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; } ;
struct adapter {TYPE_1__ upr_lock; } ;

/* Variables and functions */
 int STATUS_PENDING ; 
 int STATUS_SUCCESS ; 
 int slic_upr_queue_request (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slic_upr_start (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int slic_upr_request(struct adapter *adapter,
		     u32 upr_request,
		     u32 upr_data,
		     u32 upr_data_h,
		     u32 upr_buffer, u32 upr_buffer_h)
{
	int status;

	spin_lock_irqsave(&adapter->upr_lock.lock, adapter->upr_lock.flags);
	status = slic_upr_queue_request(adapter,
					upr_request,
					upr_data,
					upr_data_h, upr_buffer, upr_buffer_h);
	if (status != STATUS_SUCCESS) {
		spin_unlock_irqrestore(&adapter->upr_lock.lock,
					adapter->upr_lock.flags);
		return status;
	}
	slic_upr_start(adapter);
	spin_unlock_irqrestore(&adapter->upr_lock.lock,
				adapter->upr_lock.flags);
	return STATUS_PENDING;
}