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

/* Variables and functions */
 int /*<<< orphan*/  __blk_end_request_cur (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  do_pcd_request (int /*<<< orphan*/ ) ; 
 scalar_t__ pcd_busy ; 
 int /*<<< orphan*/  pcd_lock ; 
 int /*<<< orphan*/  pcd_queue ; 
 int /*<<< orphan*/ * pcd_req ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void next_request(int err)
{
	unsigned long saved_flags;

	spin_lock_irqsave(&pcd_lock, saved_flags);
	if (!__blk_end_request_cur(pcd_req, err))
		pcd_req = NULL;
	pcd_busy = 0;
	do_pcd_request(pcd_queue);
	spin_unlock_irqrestore(&pcd_lock, saved_flags);
}