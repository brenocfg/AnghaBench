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
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/ * PyImport_ImportModule (char*) ; 
 int /*<<< orphan*/  PyObject_AsFileDescriptor (int /*<<< orphan*/ *) ; 
 void* PyObject_GetAttrString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * Py_InitModule (char*,int /*<<< orphan*/ ) ; 
 void* ZFSError ; 
 int /*<<< orphan*/  zfs_prop_init () ; 
 int /*<<< orphan*/  zfsdevfd ; 
 int /*<<< orphan*/  zfsmethods ; 

void
initioctl(void)
{
	PyObject *zfs_ioctl = Py_InitModule("zfs.ioctl", zfsmethods);
	PyObject *zfs_util = PyImport_ImportModule("zfs.util");
	PyObject *devfile;

	if (zfs_util == NULL)
		return;

	ZFSError = PyObject_GetAttrString(zfs_util, "ZFSError");
	devfile = PyObject_GetAttrString(zfs_util, "dev");
	zfsdevfd = PyObject_AsFileDescriptor(devfile);

	zfs_prop_init();
}