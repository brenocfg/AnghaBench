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
struct scsi_qla_host {int phy_port_cnt; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 scalar_t__ is_qla40XX (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct scsi_qla_host* to_qla_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
qla4xxx_phy_port_cnt_show(struct device *dev, struct device_attribute *attr,
		      char *buf)
{
	struct scsi_qla_host *ha = to_qla_host(class_to_shost(dev));

	if (is_qla40XX(ha))
		return -ENOSYS;

	return snprintf(buf, PAGE_SIZE, "0x%04X\n", ha->phy_port_cnt);
}