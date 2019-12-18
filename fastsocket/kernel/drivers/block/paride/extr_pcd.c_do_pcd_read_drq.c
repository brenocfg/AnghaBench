#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ PCD_RETRIES ; 
 int /*<<< orphan*/  do_pcd_read () ; 
 int /*<<< orphan*/  do_pcd_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  next_request (int /*<<< orphan*/ ) ; 
 int pcd_bufblk ; 
 int /*<<< orphan*/  pcd_buffer ; 
 scalar_t__ pcd_completion (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* pcd_current ; 
 int /*<<< orphan*/  pcd_lock ; 
 int /*<<< orphan*/  pcd_queue ; 
 scalar_t__ pcd_retries ; 
 int /*<<< orphan*/  pcd_start ; 
 int /*<<< orphan*/  pi_do_claimed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void do_pcd_read_drq(void)
{
	unsigned long saved_flags;

	if (pcd_completion(pcd_current, pcd_buffer, "read block")) {
		if (pcd_retries < PCD_RETRIES) {
			mdelay(1);
			pcd_retries++;
			pi_do_claimed(pcd_current->pi, pcd_start);
			return;
		}
		pcd_bufblk = -1;
		next_request(-EIO);
		return;
	}

	do_pcd_read();
	spin_lock_irqsave(&pcd_lock, saved_flags);
	do_pcd_request(pcd_queue);
	spin_unlock_irqrestore(&pcd_lock, saved_flags);
}