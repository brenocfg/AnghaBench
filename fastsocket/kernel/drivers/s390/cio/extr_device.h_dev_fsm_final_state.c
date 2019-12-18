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
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ DEV_STATE_BOXED ; 
 scalar_t__ DEV_STATE_NOT_OPER ; 
 scalar_t__ DEV_STATE_OFFLINE ; 
 scalar_t__ DEV_STATE_ONLINE ; 

__attribute__((used)) static inline int
dev_fsm_final_state(struct ccw_device *cdev)
{
	return (cdev->private->state == DEV_STATE_NOT_OPER ||
		cdev->private->state == DEV_STATE_OFFLINE ||
		cdev->private->state == DEV_STATE_ONLINE ||
		cdev->private->state == DEV_STATE_BOXED);
}