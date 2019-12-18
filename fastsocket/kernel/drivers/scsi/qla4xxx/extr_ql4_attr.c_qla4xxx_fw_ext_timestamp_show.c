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
struct TYPE_2__ {char* extended_timestamp; } ;
struct scsi_qla_host {TYPE_1__ fw_info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 struct scsi_qla_host* to_qla_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
qla4xxx_fw_ext_timestamp_show(struct device *dev, struct device_attribute *attr,
			      char *buf)
{
	struct scsi_qla_host *ha = to_qla_host(class_to_shost(dev));
	return snprintf(buf, PAGE_SIZE, "%s\n", ha->fw_info.extended_timestamp);
}