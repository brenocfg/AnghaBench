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
 scalar_t__ dt_is_compatible (void*,char*) ; 
 void* finddevice (char*) ; 
 scalar_t__ getprop (void*,char*,char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  virtex_ns16550_console_init (void*) ; 

int platform_specific_init(void)
{
	void *devp;
	char devtype[MAX_PROP_LEN];
	char path[MAX_PATH_LEN];

	devp = finddevice("/chosen");
	if (devp == NULL)
		return -1;

	if (getprop(devp, "linux,stdout-path", path, MAX_PATH_LEN) > 0) {
		devp = finddevice(path);
		if (devp == NULL)
			return -1;

		if ((getprop(devp, "device_type", devtype, sizeof(devtype)) > 0)
				&& !strcmp(devtype, "serial")
				&& (dt_is_compatible(devp, "ns16550")))
				virtex_ns16550_console_init(devp);
	}
	return 0;
}