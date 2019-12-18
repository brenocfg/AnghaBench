#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {TYPE_4__* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_5__ {char* product_name; } ;
struct TYPE_7__ {char* model_number; TYPE_1__ mr; } ;

/* Variables and functions */
 scalar_t__ IS_QLAFX00 (TYPE_4__*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 TYPE_2__* shost_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static ssize_t
qla2x00_model_name_show(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));

	if (IS_QLAFX00(vha->hw))
		return snprintf(buf, PAGE_SIZE, "%s\n",
		    vha->hw->mr.product_name);

	return snprintf(buf, PAGE_SIZE, "%s\n", vha->hw->model_number);
}