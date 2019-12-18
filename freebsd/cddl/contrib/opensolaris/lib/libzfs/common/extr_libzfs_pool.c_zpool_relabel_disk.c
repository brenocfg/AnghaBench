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
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EZFS_NOCAP ; 
 int /*<<< orphan*/  EZFS_OPENFAILED ; 
 int MAXPATHLEN ; 
 int O_NDELAY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  RTLD_DEFAULT ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int VT_ENOSPC ; 
 char* ZFS_RDISK_ROOT ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dlsym (int /*<<< orphan*/ ,char*) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
zpool_relabel_disk(libzfs_handle_t *hdl, const char *name)
{
#ifdef illumos
	char path[MAXPATHLEN];
	char errbuf[1024];
	int fd, error;
	int (*_efi_use_whole_disk)(int);

	if ((_efi_use_whole_disk = (int (*)(int))dlsym(RTLD_DEFAULT,
	    "efi_use_whole_disk")) == NULL)
		return (-1);

	(void) snprintf(path, sizeof (path), "%s/%s", ZFS_RDISK_ROOT, name);

	if ((fd = open(path, O_RDWR | O_NDELAY)) < 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "cannot "
		    "relabel '%s': unable to open device"), name);
		return (zfs_error(hdl, EZFS_OPENFAILED, errbuf));
	}

	/*
	 * It's possible that we might encounter an error if the device
	 * does not have any unallocated space left. If so, we simply
	 * ignore that error and continue on.
	 */
	error = _efi_use_whole_disk(fd);
	(void) close(fd);
	if (error && error != VT_ENOSPC) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "cannot "
		    "relabel '%s': unable to read disk capacity"), name);
		return (zfs_error(hdl, EZFS_NOCAP, errbuf));
	}
#endif	/* illumos */
	return (0);
}