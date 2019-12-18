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
struct TYPE_3__ {int /*<<< orphan*/  zi_object; int /*<<< orphan*/  zi_objset; } ;
typedef  TYPE_1__ zinject_record_t ;
struct stat64 {int /*<<< orphan*/  st_ino; } ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DMU_OST_ZFS ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_objset_id (int /*<<< orphan*/ *) ; 
 int dmu_objset_own (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 
 int /*<<< orphan*/  sync () ; 

__attribute__((used)) static int
object_from_path(const char *dataset, const char *path, struct stat64 *statbuf,
    zinject_record_t *record)
{
	objset_t *os;
	int err;

	/*
	 * Before doing any libzpool operations, call sync() to ensure that the
	 * on-disk state is consistent with the in-core state.
	 */
	sync();

	err = dmu_objset_own(dataset, DMU_OST_ZFS, B_TRUE, FTAG, &os);
	if (err != 0) {
		(void) fprintf(stderr, "cannot open dataset '%s': %s\n",
		    dataset, strerror(err));
		return (-1);
	}

	record->zi_objset = dmu_objset_id(os);
	record->zi_object = statbuf->st_ino;

	dmu_objset_disown(os, FTAG);

	return (0);
}