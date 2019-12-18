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

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_usbip_debug ; 
 int /*<<< orphan*/  dev_attr_usbip_sockfd ; 
 int /*<<< orphan*/  dev_attr_usbip_status ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stub_add_files(struct device *dev)
{
	int err = 0;

	err = device_create_file(dev, &dev_attr_usbip_status);
	if (err)
		goto err_status;

	err = device_create_file(dev, &dev_attr_usbip_sockfd);
	if (err)
		goto err_sockfd;

	err = device_create_file(dev, &dev_attr_usbip_debug);
	if (err)
		goto err_debug;

	return 0;

err_debug:
	device_remove_file(dev, &dev_attr_usbip_sockfd);

err_sockfd:
	device_remove_file(dev, &dev_attr_usbip_status);

err_status:
	return err;
}