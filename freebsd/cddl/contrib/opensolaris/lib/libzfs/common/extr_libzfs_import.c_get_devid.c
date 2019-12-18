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
typedef  int /*<<< orphan*/  ddi_devid_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  devid_free (int /*<<< orphan*/ ) ; 
 scalar_t__ devid_get (int,int /*<<< orphan*/ *) ; 
 scalar_t__ devid_get_minor_name (int,char**) ; 
 char* devid_str_encode (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devid_str_free (char*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
get_devid(const char *path)
{
#ifdef have_devid
	int fd;
	ddi_devid_t devid;
	char *minor, *ret;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);

	minor = NULL;
	ret = NULL;
	if (devid_get(fd, &devid) == 0) {
		if (devid_get_minor_name(fd, &minor) == 0)
			ret = devid_str_encode(devid, minor);
		if (minor != NULL)
			devid_str_free(minor);
		devid_free(devid);
	}
	(void) close(fd);

	return (ret);
#else
	return (NULL);
#endif
}