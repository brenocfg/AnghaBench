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
struct device_attribute {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  shost_dev; TYPE_1__* hostt; } ;
struct TYPE_2__ {struct device_attribute** shost_attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,struct device_attribute*) ; 

__attribute__((used)) static void srp_del_scsi_host_attr(struct Scsi_Host *shost)
{
	struct device_attribute **attr;

	for (attr = shost->hostt->shost_attrs; attr && *attr; ++attr)
		device_remove_file(&shost->shost_dev, *attr);
}