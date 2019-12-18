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
struct device {int dummy; } ;
struct ata_port {int flags; TYPE_1__* ops; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* em_show ) (struct ata_port*,char*) ;} ;

/* Variables and functions */
 int ATA_FLAG_EM ; 
 int /*<<< orphan*/  EINVAL ; 
 struct ata_port* ata_shost_to_port (struct Scsi_Host*) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct ata_port*,char*) ; 

__attribute__((used)) static ssize_t
ata_scsi_em_message_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct ata_port *ap = ata_shost_to_port(shost);

	if (ap->ops->em_show && (ap->flags & ATA_FLAG_EM))
		return ap->ops->em_show(ap, buf);
	return -EINVAL;
}