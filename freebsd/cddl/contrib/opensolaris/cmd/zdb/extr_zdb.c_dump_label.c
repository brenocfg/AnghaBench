#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* vp_nvlist; } ;
struct TYPE_6__ {TYPE_1__ vl_vdev_phys; } ;
typedef  TYPE_2__ vdev_label_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct stat64 {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  label ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  P2ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_MINBLOCKSHIFT ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 int VDEV_LABELS ; 
 int /*<<< orphan*/  ZFS_DISK_ROOTD ; 
 char* ZFS_RDISK_ROOTD ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ASHIFT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dump_label_uberblocks (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_nvlist (int /*<<< orphan*/ *,int) ; 
 scalar_t__* dump_opt ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 scalar_t__ fstat64 (int,struct stat64*) ; 
 int /*<<< orphan*/  isdigit (char) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_unpack (char*,size_t,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int open64 (char*,int /*<<< orphan*/ ) ; 
 int pread64 (int,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 scalar_t__ stat64 (char*,struct stat64*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,char) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/  vdev_label_offset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_label(const char *dev)
{
	int fd;
	vdev_label_t label;
	char path[MAXPATHLEN];
	char *buf = label.vl_vdev_phys.vp_nvlist;
	size_t buflen = sizeof (label.vl_vdev_phys.vp_nvlist);
	struct stat64 statbuf;
	uint64_t psize, ashift;
	boolean_t label_found = B_FALSE;

	(void) strlcpy(path, dev, sizeof (path));
	if (dev[0] == '/') {
		if (strncmp(dev, ZFS_DISK_ROOTD,
		    strlen(ZFS_DISK_ROOTD)) == 0) {
			(void) snprintf(path, sizeof (path), "%s%s",
			    ZFS_RDISK_ROOTD, dev + strlen(ZFS_DISK_ROOTD));
		}
	} else if (stat64(path, &statbuf) != 0) {
		char *s;

		(void) snprintf(path, sizeof (path), "%s%s", ZFS_RDISK_ROOTD,
		    dev);
		if (((s = strrchr(dev, 's')) == NULL &&
		    (s = strchr(dev, 'p')) == NULL) ||
		    !isdigit(*(s + 1)))
			(void) strlcat(path, "s0", sizeof (path));
	}

	if ((fd = open64(path, O_RDONLY)) < 0) {
		(void) fprintf(stderr, "cannot open '%s': %s\n", path,
		    strerror(errno));
		exit(1);
	}

	if (fstat64(fd, &statbuf) != 0) {
		(void) fprintf(stderr, "failed to stat '%s': %s\n", path,
		    strerror(errno));
		(void) close(fd);
		exit(1);
	}

	if (S_ISBLK(statbuf.st_mode)) {
		(void) fprintf(stderr,
		    "cannot use '%s': character device required\n", path);
		(void) close(fd);
		exit(1);
	}

	psize = statbuf.st_size;
	psize = P2ALIGN(psize, (uint64_t)sizeof (vdev_label_t));

	for (int l = 0; l < VDEV_LABELS; l++) {
		nvlist_t *config = NULL;

		if (!dump_opt['q']) {
			(void) printf("------------------------------------\n");
			(void) printf("LABEL %d\n", l);
			(void) printf("------------------------------------\n");
		}

		if (pread64(fd, &label, sizeof (label),
		    vdev_label_offset(psize, l, 0)) != sizeof (label)) {
			if (!dump_opt['q'])
				(void) printf("failed to read label %d\n", l);
			continue;
		}

		if (nvlist_unpack(buf, buflen, &config, 0) != 0) {
			if (!dump_opt['q'])
				(void) printf("failed to unpack label %d\n", l);
			ashift = SPA_MINBLOCKSHIFT;
		} else {
			nvlist_t *vdev_tree = NULL;

			if (!dump_opt['q'])
				dump_nvlist(config, 4);
			if ((nvlist_lookup_nvlist(config,
			    ZPOOL_CONFIG_VDEV_TREE, &vdev_tree) != 0) ||
			    (nvlist_lookup_uint64(vdev_tree,
			    ZPOOL_CONFIG_ASHIFT, &ashift) != 0))
				ashift = SPA_MINBLOCKSHIFT;
			nvlist_free(config);
			label_found = B_TRUE;
		}
		if (dump_opt['u'])
			dump_label_uberblocks(&label, ashift);
	}

	(void) close(fd);

	return (label_found ? 0 : 2);
}