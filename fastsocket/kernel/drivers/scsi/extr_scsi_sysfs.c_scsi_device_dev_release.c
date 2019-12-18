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
struct scsi_device {int /*<<< orphan*/  ew; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  execute_in_process_context (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_device_dev_release_usercontext ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static void scsi_device_dev_release(struct device *dev)
{
	struct scsi_device *sdp = to_scsi_device(dev);
	execute_in_process_context(scsi_device_dev_release_usercontext,
				   &sdp->ew);
}