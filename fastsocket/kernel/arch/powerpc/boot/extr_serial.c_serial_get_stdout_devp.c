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
typedef  int /*<<< orphan*/  devtype ;

/* Variables and functions */
 int MAX_PATH_LEN ; 
 int MAX_PROP_LEN ; 
 void* finddevice (char*) ; 
 scalar_t__ getprop (void*,char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void *serial_get_stdout_devp(void)
{
	void *devp;
	char devtype[MAX_PROP_LEN];
	char path[MAX_PATH_LEN];

	devp = finddevice("/chosen");
	if (devp == NULL)
		goto err_out;

	if (getprop(devp, "linux,stdout-path", path, MAX_PATH_LEN) > 0) {
		devp = finddevice(path);
		if (devp == NULL)
			goto err_out;

		if ((getprop(devp, "device_type", devtype, sizeof(devtype)) > 0)
				&& !strcmp(devtype, "serial"))
			return devp;
	}
err_out:
	return NULL;
}