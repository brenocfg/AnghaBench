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
typedef  int /*<<< orphan*/  uint ;
struct scsi_device {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct scsi_device*) ; 
 int PTR_ERR (struct scsi_device*) ; 
 struct scsi_device* __scsi_add_device (struct Scsi_Host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_device_put (struct scsi_device*) ; 

int scsi_add_device(struct Scsi_Host *host, uint channel,
		    uint target, uint lun)
{
	struct scsi_device *sdev = 
		__scsi_add_device(host, channel, target, lun, NULL);
	if (IS_ERR(sdev))
		return PTR_ERR(sdev);

	scsi_device_put(sdev);
	return 0;
}