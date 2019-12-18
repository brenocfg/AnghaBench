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
 int /*<<< orphan*/  scsi_remove_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_scsi_device (struct device*) ; 

__attribute__((used)) static void sdev_store_delete_callback(struct device *dev)
{
	scsi_remove_device(to_scsi_device(dev));
}