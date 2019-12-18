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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  Word; } ;
struct TYPE_4__ {TYPE_1__ NvdataVersionPersistent; } ;
struct MPT2SAS_ADAPTER {TYPE_2__ iounit_pg0; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct MPT2SAS_ADAPTER* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t
_ctl_version_nvdata_persistent_show(struct device *cdev,
    struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct MPT2SAS_ADAPTER *ioc = shost_priv(shost);

	return snprintf(buf, PAGE_SIZE, "%08xh\n",
	    le32_to_cpu(ioc->iounit_pg0.NvdataVersionPersistent.Word));
}