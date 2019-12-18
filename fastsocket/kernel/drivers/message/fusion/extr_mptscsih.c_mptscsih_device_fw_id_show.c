#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_device {TYPE_2__* hostdata; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {TYPE_1__* vtarget; } ;
typedef  TYPE_2__ VirtDevice ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 struct scsi_device* to_scsi_device (struct device*) ; 

__attribute__((used)) static ssize_t
mptscsih_device_fw_id_show(struct device *dev, struct device_attribute *attr,
    char *buf)
{
	struct scsi_device *sdev = to_scsi_device(dev);
	VirtDevice *vdevice = sdev->hostdata;

	if (vdevice && vdevice->vtarget)
		return snprintf(buf, PAGE_SIZE, "0x%04x\n",
		    vdevice->vtarget->id);
	else
		return snprintf(buf, PAGE_SIZE, "0x0\n");
}