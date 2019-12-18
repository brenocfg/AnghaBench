#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct qla_hw_data {TYPE_1__* cs84xx; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_5__ {scalar_t__ op_fw_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_QLA84XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 int qla84xx_verify_chip (TYPE_2__*,scalar_t__*) ; 
 TYPE_2__* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ssize_t
qla24xx_84xx_fw_version_show(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	int rval = QLA_SUCCESS;
	uint16_t status[2] = {0, 0};
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	struct qla_hw_data *ha = vha->hw;

	if (!IS_QLA84XX(ha))
		return snprintf(buf, PAGE_SIZE, "\n");

	if (ha->cs84xx->op_fw_version == 0)
		rval = qla84xx_verify_chip(vha, status);

	if ((rval == QLA_SUCCESS) && (status[0] == 0))
		return snprintf(buf, PAGE_SIZE, "%u\n",
			(uint32_t)ha->cs84xx->op_fw_version);

	return snprintf(buf, PAGE_SIZE, "\n");
}