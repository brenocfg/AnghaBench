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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ata_port {int /*<<< orphan*/  pm_policy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 char* ata_scsi_lpm_get (int /*<<< orphan*/ ) ; 
 struct ata_port* ata_shost_to_port (struct Scsi_Host*) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static ssize_t
ata_scsi_lpm_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct ata_port *ap = ata_shost_to_port(shost);
	const char *policy =
		ata_scsi_lpm_get(ap->pm_policy);

	if (!policy)
		return -EINVAL;

	return snprintf(buf, 23, "%s\n", policy);
}