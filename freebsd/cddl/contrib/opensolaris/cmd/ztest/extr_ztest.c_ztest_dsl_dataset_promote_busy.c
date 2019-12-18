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
struct TYPE_3__ {char* zd_name; } ;
typedef  TYPE_1__ ztest_ds_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  snap3name ;
typedef  int /*<<< orphan*/  snap2name ;
typedef  int /*<<< orphan*/  snap1name ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  clone2name ;
typedef  int /*<<< orphan*/  clone1name ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DMU_OST_ANY ; 
 int EBUSY ; 
 int EEXIST ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_READER ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int dmu_objset_clone (char*,char*) ; 
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dmu_objset_own (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int dmu_objset_snapshot_one (char*,scalar_t__) ; 
 int dsl_dataset_promote (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  ztest_dsl_dataset_cleanup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_name_lock ; 
 int /*<<< orphan*/  ztest_record_enospc (int /*<<< orphan*/ ) ; 

void
ztest_dsl_dataset_promote_busy(ztest_ds_t *zd, uint64_t id)
{
	objset_t *os;
	char snap1name[ZFS_MAX_DATASET_NAME_LEN];
	char clone1name[ZFS_MAX_DATASET_NAME_LEN];
	char snap2name[ZFS_MAX_DATASET_NAME_LEN];
	char clone2name[ZFS_MAX_DATASET_NAME_LEN];
	char snap3name[ZFS_MAX_DATASET_NAME_LEN];
	char *osname = zd->zd_name;
	int error;

	rw_enter(&ztest_name_lock, RW_READER);

	ztest_dsl_dataset_cleanup(osname, id);

	(void) snprintf(snap1name, sizeof (snap1name),
	    "%s@s1_%llu", osname, id);
	(void) snprintf(clone1name, sizeof (clone1name),
	    "%s/c1_%llu", osname, id);
	(void) snprintf(snap2name, sizeof (snap2name),
	    "%s@s2_%llu", clone1name, id);
	(void) snprintf(clone2name, sizeof (clone2name),
	    "%s/c2_%llu", osname, id);
	(void) snprintf(snap3name, sizeof (snap3name),
	    "%s@s3_%llu", clone1name, id);

	error = dmu_objset_snapshot_one(osname, strchr(snap1name, '@') + 1);
	if (error && error != EEXIST) {
		if (error == ENOSPC) {
			ztest_record_enospc(FTAG);
			goto out;
		}
		fatal(0, "dmu_take_snapshot(%s) = %d", snap1name, error);
	}

	error = dmu_objset_clone(clone1name, snap1name);
	if (error) {
		if (error == ENOSPC) {
			ztest_record_enospc(FTAG);
			goto out;
		}
		fatal(0, "dmu_objset_create(%s) = %d", clone1name, error);
	}

	error = dmu_objset_snapshot_one(clone1name, strchr(snap2name, '@') + 1);
	if (error && error != EEXIST) {
		if (error == ENOSPC) {
			ztest_record_enospc(FTAG);
			goto out;
		}
		fatal(0, "dmu_open_snapshot(%s) = %d", snap2name, error);
	}

	error = dmu_objset_snapshot_one(clone1name, strchr(snap3name, '@') + 1);
	if (error && error != EEXIST) {
		if (error == ENOSPC) {
			ztest_record_enospc(FTAG);
			goto out;
		}
		fatal(0, "dmu_open_snapshot(%s) = %d", snap3name, error);
	}

	error = dmu_objset_clone(clone2name, snap3name);
	if (error) {
		if (error == ENOSPC) {
			ztest_record_enospc(FTAG);
			goto out;
		}
		fatal(0, "dmu_objset_create(%s) = %d", clone2name, error);
	}

	error = dmu_objset_own(snap2name, DMU_OST_ANY, B_TRUE, FTAG, &os);
	if (error)
		fatal(0, "dmu_objset_own(%s) = %d", snap2name, error);
	error = dsl_dataset_promote(clone2name, NULL);
	if (error == ENOSPC) {
		dmu_objset_disown(os, FTAG);
		ztest_record_enospc(FTAG);
		goto out;
	}
	if (error != EBUSY)
		fatal(0, "dsl_dataset_promote(%s), %d, not EBUSY", clone2name,
		    error);
	dmu_objset_disown(os, FTAG);

out:
	ztest_dsl_dataset_cleanup(osname, id);

	rw_exit(&ztest_name_lock);
}