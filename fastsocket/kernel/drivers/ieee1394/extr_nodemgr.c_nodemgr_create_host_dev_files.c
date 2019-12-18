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
struct device {int dummy; } ;
struct hpsb_host {struct device device; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPSB_ERR (char*) ; 
 scalar_t__ device_create_file (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fw_host_attrs ; 

__attribute__((used)) static void nodemgr_create_host_dev_files(struct hpsb_host *host)
{
	struct device *dev = &host->device;
	int i;

	for (i = 0; i < ARRAY_SIZE(fw_host_attrs); i++)
		if (device_create_file(dev, fw_host_attrs[i]))
			goto fail;
	return;
fail:
	HPSB_ERR("Failed to add sysfs attribute");
}