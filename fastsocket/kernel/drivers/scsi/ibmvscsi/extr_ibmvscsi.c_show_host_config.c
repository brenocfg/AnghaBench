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
struct ibmvscsi_host_data {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 scalar_t__ ibmvscsi_do_host_config (struct ibmvscsi_host_data*,char*,int /*<<< orphan*/ ) ; 
 struct ibmvscsi_host_data* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t show_host_config(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct Scsi_Host *shost = class_to_shost(dev);
	struct ibmvscsi_host_data *hostdata = shost_priv(shost);

	/* returns null-terminated host config data */
	if (ibmvscsi_do_host_config(hostdata, buf, PAGE_SIZE) == 0)
		return strlen(buf);
	else
		return 0;
}