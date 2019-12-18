#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ata_port {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  size_t ssize_t ;
typedef  enum link_pm { ____Placeholder_link_pm } link_pm ;
struct TYPE_3__ {int value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  ata_lpm_schedule (struct ata_port*,int) ; 
 struct ata_port* ata_shost_to_port (struct Scsi_Host*) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 TYPE_1__* link_pm_policy ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int const) ; 

__attribute__((used)) static ssize_t ata_scsi_lpm_put(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct ata_port *ap = ata_shost_to_port(shost);
	enum link_pm policy = 0;
	int i;

	/*
	 * we are skipping array location 0 on purpose - this
	 * is because a value of NOT_AVAILABLE is displayed
	 * to the user as max_performance, but when the user
	 * writes "max_performance", they actually want the
	 * value to match MAX_PERFORMANCE.
	 */
	for (i = 1; i < ARRAY_SIZE(link_pm_policy); i++) {
		const int len = strlen(link_pm_policy[i].name);
		if (strncmp(link_pm_policy[i].name, buf, len) == 0 &&
		   buf[len] == '\n') {
			policy = link_pm_policy[i].value;
			break;
		}
	}
	if (!policy)
		return -EINVAL;

	ata_lpm_schedule(ap, policy);
	return count;
}