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
struct scsi_disk {size_t provisioning_mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char** lbp_mode ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 struct scsi_disk* to_scsi_disk (struct device*) ; 

__attribute__((used)) static ssize_t
sd_show_provisioning_mode(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	struct scsi_disk *sdkp = to_scsi_disk(dev);

	return snprintf(buf, 20, "%s\n", lbp_mode[sdkp->provisioning_mode]);
}