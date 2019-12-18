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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDEV_RUNNING ; 
 int /*<<< orphan*/  __scsi_target_unblock (struct device*,int /*<<< orphan*/ ) ; 

void
scsi_target_unblock(struct device *dev)
{
	__scsi_target_unblock(dev, SDEV_RUNNING);
}