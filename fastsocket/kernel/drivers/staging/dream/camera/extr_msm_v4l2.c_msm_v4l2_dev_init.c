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
struct msm_v4l2_device {int /*<<< orphan*/  read_queue; int /*<<< orphan*/  read_queue_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __SPIN_LOCK_UNLOCKED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msm_v4l2_dev_init(struct msm_v4l2_device *pmsm_v4l2_dev)
{
	pmsm_v4l2_dev->read_queue_lock =
	    __SPIN_LOCK_UNLOCKED(pmsm_v4l2_dev->read_queue_lock);
	INIT_LIST_HEAD(&pmsm_v4l2_dev->read_queue);
}