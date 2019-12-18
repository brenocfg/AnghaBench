#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  devname; } ;
typedef  TYPE_1__ devid_nmlist_t ;
typedef  int /*<<< orphan*/  ddi_devid_t ;

/* Variables and functions */
 int devid_deviceid_to_nmlist (char*,int /*<<< orphan*/ ,char*,TYPE_1__**) ; 
 int /*<<< orphan*/  devid_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devid_free_nmlist (TYPE_1__*) ; 
 scalar_t__ devid_str_decode (char*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  devid_str_free (char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
devid_to_path(char *devid_str)
{
	ddi_devid_t devid;
	char *minor;
	char *path;
	devid_nmlist_t *list = NULL;
	int ret;

	if (devid_str_decode(devid_str, &devid, &minor) != 0)
		return (NULL);

	ret = devid_deviceid_to_nmlist("/dev", devid, minor, &list);

	devid_str_free(minor);
	devid_free(devid);

	if (ret != 0)
		return (NULL);

	/*
	 * In a case the strdup() fails, we will just return NULL below.
	 */
	path = strdup(list[0].devname);

	devid_free_nmlist(list);

	return (path);
}