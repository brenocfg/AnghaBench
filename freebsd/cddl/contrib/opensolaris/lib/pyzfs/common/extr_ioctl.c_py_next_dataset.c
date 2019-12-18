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
struct TYPE_4__ {int /*<<< orphan*/  zc_cookie; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ ESRCH ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,char**,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyErr_SetNone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyExc_StopIteration ; 
 int /*<<< orphan*/ * Py_BuildValue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int ZFS_IOC_DATASET_LIST_NEXT ; 
 int ZFS_IOC_SNAPSHOT_LIST_NEXT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_ds_props (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * ioctl_with_dstnv (int,TYPE_1__*) ; 
 int /*<<< orphan*/  seterr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static PyObject *
py_next_dataset(PyObject *self, PyObject *args)
{
	int ioc;
	uint64_t cookie;
	zfs_cmd_t zc = { 0 };
	int snaps;
	char *name;
	PyObject *nvl;
	PyObject *ret = NULL;

	if (!PyArg_ParseTuple(args, "siK", &name, &snaps, &cookie))
		return (NULL);

	(void) strlcpy(zc.zc_name, name, sizeof (zc.zc_name));
	zc.zc_cookie = cookie;

	if (snaps)
		ioc = ZFS_IOC_SNAPSHOT_LIST_NEXT;
	else
		ioc = ZFS_IOC_DATASET_LIST_NEXT;

	nvl = ioctl_with_dstnv(ioc, &zc);
	if (nvl) {
		add_ds_props(&zc, nvl);
		ret = Py_BuildValue("sKO", zc.zc_name, zc.zc_cookie, nvl);
		Py_DECREF(nvl);
	} else if (errno == ESRCH) {
		PyErr_SetNone(PyExc_StopIteration);
	} else {
		if (snaps)
			seterr(_("cannot get snapshots of %s"), name);
		else
			seterr(_("cannot get child datasets of %s"), name);
	}
	return (ret);
}