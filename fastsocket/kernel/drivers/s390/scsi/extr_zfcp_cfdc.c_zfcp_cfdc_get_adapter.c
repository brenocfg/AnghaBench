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
typedef  int u32 ;
struct zfcp_adapter {int dummy; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  busid ;

/* Variables and functions */
 struct zfcp_adapter* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct ccw_device* get_ccwdev_by_busid (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  zfcp_adapter_get (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_ccw_driver ; 

__attribute__((used)) static struct zfcp_adapter *zfcp_cfdc_get_adapter(u32 devno)
{
	char busid[9];
	struct ccw_device *ccwdev;
	struct zfcp_adapter *adapter = NULL;

	snprintf(busid, sizeof(busid), "0.0.%04x", devno);
	ccwdev = get_ccwdev_by_busid(&zfcp_ccw_driver, busid);
	if (!ccwdev)
		goto out;

	adapter = dev_get_drvdata(&ccwdev->dev);
	if (!adapter)
		goto out_put;

	zfcp_adapter_get(adapter);
out_put:
	put_device(&ccwdev->dev);
out:
	return adapter;
}