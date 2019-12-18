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
struct TYPE_3__ {size_t zc_nvlist_src_size; uintptr_t zc_nvlist_src; int zc_perm_action; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  NV_ENCODE_NATIVE ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,char**,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  PyDict_Type ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  ZFS_IOC_SET_FSACL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * dict2nvl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ioctl_with_cmdstr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* malloc (size_t) ; 
 int nvlist_pack (int /*<<< orphan*/ *,char**,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvlist_size (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seterr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static PyObject *
py_set_fsacl(PyObject *self, PyObject *args)
{
	int un;
	size_t nvsz;
	zfs_cmd_t zc = { 0 };
	char *name, *nvbuf;
	PyObject *dict, *file;
	nvlist_t *nvl;
	int err;

	if (!PyArg_ParseTuple(args, "siO!", &name, &un,
	    &PyDict_Type, &dict))
		return (NULL);

	nvl = dict2nvl(dict);
	if (nvl == NULL)
		return (NULL);

	err = nvlist_size(nvl, &nvsz, NV_ENCODE_NATIVE);
	assert(err == 0);
	nvbuf = malloc(nvsz);
	err = nvlist_pack(nvl, &nvbuf, &nvsz, NV_ENCODE_NATIVE, 0);
	assert(err == 0);

	(void) strlcpy(zc.zc_name, name, sizeof (zc.zc_name));
	zc.zc_nvlist_src_size = nvsz;
	zc.zc_nvlist_src = (uintptr_t)nvbuf;
	zc.zc_perm_action = un;

	err = ioctl_with_cmdstr(ZFS_IOC_SET_FSACL, &zc);
	free(nvbuf);
	if (err) {
		seterr(_("cannot set permissions on %s"), name);
		return (NULL);
	}

	Py_RETURN_NONE;
}