#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  ZFS_IOC_GET_FSACL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * ioctl_with_dstnv (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  seterr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static PyObject *
py_get_fsacl(PyObject *self, PyObject *args)
{
	zfs_cmd_t zc = { 0 };
	char *name;
	PyObject *nvl;

	if (!PyArg_ParseTuple(args, "s", &name))
		return (NULL);

	(void) strlcpy(zc.zc_name, name, sizeof (zc.zc_name));

	nvl = ioctl_with_dstnv(ZFS_IOC_GET_FSACL, &zc);
	if (nvl == NULL)
		seterr(_("cannot get permissions on %s"), name);

	return (nvl);
}