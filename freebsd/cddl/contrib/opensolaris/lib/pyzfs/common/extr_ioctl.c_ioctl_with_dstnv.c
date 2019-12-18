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
struct TYPE_4__ {int zc_nvlist_dst_size; uintptr_t zc_nvlist_dst; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/ * nvl2py (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_unpack (void*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfsdevfd ; 

__attribute__((used)) static PyObject *
ioctl_with_dstnv(int ioc, zfs_cmd_t *zc)
{
	int nvsz = 2048;
	void *nvbuf;
	PyObject *pynv = NULL;

again:
	nvbuf = malloc(nvsz);
	zc->zc_nvlist_dst_size = nvsz;
	zc->zc_nvlist_dst = (uintptr_t)nvbuf;

	if (ioctl(zfsdevfd, ioc, zc) == 0) {
		nvlist_t *nvl;

		errno = nvlist_unpack(nvbuf, zc->zc_nvlist_dst_size, &nvl, 0);
		if (errno == 0) {
			pynv = nvl2py(nvl);
			nvlist_free(nvl);
		}
	} else if (errno == ENOMEM) {
		free(nvbuf);
		nvsz = zc->zc_nvlist_dst_size;
		goto again;
	}
	free(nvbuf);
	return (pynv);
}