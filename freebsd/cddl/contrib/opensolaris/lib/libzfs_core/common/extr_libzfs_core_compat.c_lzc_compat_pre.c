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
typedef  int zfs_ioc_t ;
struct TYPE_3__ {int zc_cleanup_fd; int /*<<< orphan*/  zc_string; int /*<<< orphan*/  zc_value; int /*<<< orphan*/  zc_name; int /*<<< orphan*/  zc_objset_type; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int int32_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int MAXNAMELEN ; 
 int MAXPATHLEN ; 
 scalar_t__ ZFS_IOCVER_LZC ; 
#define  ZFS_IOC_CLONE 134 
#define  ZFS_IOC_CREATE 133 
#define  ZFS_IOC_DESTROY_SNAPS 132 
#define  ZFS_IOC_HOLD 131 
#define  ZFS_IOC_RELEASE 130 
#define  ZFS_IOC_SNAPSHOT 129 
#define  ZFS_IOC_SPACE_SNAPS 128 
 int /*<<< orphan*/  fnvlist_lookup_int32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * fnvlist_lookup_nvlist (int /*<<< orphan*/ *,char*) ; 
 char* fnvlist_lookup_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_lookup_int32 (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  nvlist_lookup_nvlist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  nvpair_value_string (int /*<<< orphan*/ *,char**) ; 
 int strcspn (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ zfs_ioctl_version ; 

int
lzc_compat_pre(zfs_cmd_t *zc, zfs_ioc_t *ioc, nvlist_t **source)
{
	nvlist_t *nvl = NULL;
	nvpair_t *pair, *hpair;
	char *buf, *val;
	zfs_ioc_t vecnum;
	uint32_t type32;
	int32_t cleanup_fd;
	int error = 0;
	int pos;

	if (zfs_ioctl_version >= ZFS_IOCVER_LZC)
		return (0);

	vecnum = *ioc;

	switch (vecnum) {
	case ZFS_IOC_CREATE:
		type32 = fnvlist_lookup_int32(*source, "type");
		zc->zc_objset_type = (uint64_t)type32;
		nvlist_lookup_nvlist(*source, "props", &nvl);
		*source = nvl;
	break;
	case ZFS_IOC_CLONE:
		buf = fnvlist_lookup_string(*source, "origin");
		strlcpy(zc->zc_value, buf, MAXPATHLEN);
		nvlist_lookup_nvlist(*source, "props", &nvl);
		*ioc = ZFS_IOC_CREATE;
		*source = nvl;
	break;
	case ZFS_IOC_SNAPSHOT:
		nvl = fnvlist_lookup_nvlist(*source, "snaps");
		pair = nvlist_next_nvpair(nvl, NULL);
		if (pair != NULL) {
			buf = nvpair_name(pair);
			pos = strcspn(buf, "@");
			strlcpy(zc->zc_name, buf, pos + 1);
			strlcpy(zc->zc_value, buf + pos + 1, MAXPATHLEN);
		} else
			error = EINVAL;
		/* old kernel cannot create multiple snapshots */
		if (!error && nvlist_next_nvpair(nvl, pair) != NULL)
			error = EOPNOTSUPP;
		nvlist_free(nvl);
		nvl = NULL;
		nvlist_lookup_nvlist(*source, "props", &nvl);
		*source = nvl;
	break;
	case ZFS_IOC_SPACE_SNAPS:
		buf = fnvlist_lookup_string(*source, "firstsnap");
		strlcpy(zc->zc_value, buf, MAXPATHLEN);
	break;
	case ZFS_IOC_DESTROY_SNAPS:
		nvl = fnvlist_lookup_nvlist(*source, "snaps");
		pair = nvlist_next_nvpair(nvl, NULL);
		if (pair != NULL) {
			buf = nvpair_name(pair);
			pos = strcspn(buf, "@");
			strlcpy(zc->zc_name, buf, pos + 1);
		} else
			error = EINVAL;
		/* old kernel cannot atomically destroy multiple snaps */
		if (!error && nvlist_next_nvpair(nvl, pair) != NULL)
			error = EOPNOTSUPP;
		*source = nvl;
	break;
	case ZFS_IOC_HOLD:
		nvl = fnvlist_lookup_nvlist(*source, "holds");
		pair = nvlist_next_nvpair(nvl, NULL);
		if (pair != NULL) {
			buf = nvpair_name(pair);
			pos = strcspn(buf, "@");
			strlcpy(zc->zc_name, buf, pos + 1);
			strlcpy(zc->zc_value, buf + pos + 1, MAXPATHLEN);
			if (nvpair_value_string(pair, &val) == 0)
				strlcpy(zc->zc_string, val, MAXNAMELEN);
			else
				error = EINVAL;
		} else
			error = EINVAL;
		/* old kernel cannot atomically create multiple holds */
		if (!error && nvlist_next_nvpair(nvl, pair) != NULL)
			error = EOPNOTSUPP;
		nvlist_free(nvl);
		if (nvlist_lookup_int32(*source, "cleanup_fd",
		    &cleanup_fd) == 0)
			zc->zc_cleanup_fd = cleanup_fd;
		else
			zc->zc_cleanup_fd = -1;
	break;
	case ZFS_IOC_RELEASE:
		pair = nvlist_next_nvpair(*source, NULL);
		if (pair != NULL) {
			buf = nvpair_name(pair);
			pos = strcspn(buf, "@");
			strlcpy(zc->zc_name, buf, pos + 1);
			strlcpy(zc->zc_value, buf + pos + 1, MAXPATHLEN);
			if (nvpair_value_nvlist(pair, &nvl) == 0) {
				hpair = nvlist_next_nvpair(nvl, NULL);
				if (hpair != NULL)
					strlcpy(zc->zc_string,
					    nvpair_name(hpair), MAXNAMELEN);
				else
					error = EINVAL;
				if (!error && nvlist_next_nvpair(nvl,
				    hpair) != NULL)
					error = EOPNOTSUPP;
			} else
				error = EINVAL;
		} else
			error = EINVAL;
		/* old kernel cannot atomically release multiple holds */
		if (!error && nvlist_next_nvpair(nvl, pair) != NULL)
			error = EOPNOTSUPP;
	break;
	}

	return (error);
}