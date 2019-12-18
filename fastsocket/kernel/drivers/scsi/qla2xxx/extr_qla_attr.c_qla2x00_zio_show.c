#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_5__ {TYPE_1__* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
struct TYPE_4__ {int zio_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
#define  QLA_ZIO_DISABLED 129 
#define  QLA_ZIO_MODE_6 128 
 int /*<<< orphan*/  class_to_shost (struct device*) ; 
 TYPE_2__* shost_priv (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t
qla2x00_zio_show(struct device *dev, struct device_attribute *attr,
		 char *buf)
{
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	int len = 0;

	switch (vha->hw->zio_mode) {
	case QLA_ZIO_MODE_6:
		len += snprintf(buf + len, PAGE_SIZE-len, "Mode 6\n");
		break;
	case QLA_ZIO_DISABLED:
		len += snprintf(buf + len, PAGE_SIZE-len, "Disabled\n");
		break;
	}
	return len;
}