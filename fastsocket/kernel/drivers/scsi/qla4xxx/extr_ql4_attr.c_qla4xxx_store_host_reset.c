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
struct scsi_qla_host {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int qla4xxx_check_reset_type (char*) ; 
 int qla4xxx_host_reset (struct scsi_qla_host*,int) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,char*) ; 
 struct scsi_qla_host* to_qla_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
qla4xxx_store_host_reset(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct scsi_qla_host *ha = to_qla_host(class_to_shost(dev));
	int ret = -EINVAL;
	char str[10];
	int type;

	sscanf(buf, "%s", str);
	type = qla4xxx_check_reset_type(str);

	if (!type)
		goto exit_store_host_reset;

	ret = qla4xxx_host_reset(ha, type);

exit_store_host_reset:
	if (ret == 0)
		ret = count;
	return ret;
}