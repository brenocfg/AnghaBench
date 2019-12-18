#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  used ;
typedef  int /*<<< orphan*/  unique ;
typedef  int /*<<< orphan*/  uncompressed ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  char* u_longlong_t ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_2__ {scalar_t__ ds_props_obj; scalar_t__ ds_next_clones_obj; scalar_t__ ds_flags; scalar_t__ ds_guid; scalar_t__ ds_fsid_guid; scalar_t__ ds_deadlist_obj; scalar_t__ ds_creation_txg; scalar_t__ ds_userrefs_obj; scalar_t__ ds_num_children; scalar_t__ ds_snapnames_zapobj; scalar_t__ ds_next_snap_obj; scalar_t__ ds_prev_snap_txg; scalar_t__ ds_prev_snap_obj; scalar_t__ ds_dir_obj; int /*<<< orphan*/  ds_bp; int /*<<< orphan*/  ds_unique_bytes; int /*<<< orphan*/  ds_uncompressed_bytes; int /*<<< orphan*/  ds_compressed_bytes; int /*<<< orphan*/  ds_referenced_bytes; int /*<<< orphan*/  ds_creation_time; } ;
typedef  TYPE_1__ dsl_dataset_phys_t ;
typedef  int /*<<< orphan*/  compressed ;
typedef  int /*<<< orphan*/  blkbuf ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BP_SPRINTF_LEN ; 
 int /*<<< orphan*/  CTASSERT (int) ; 
 int NN_NUMBUF_SZ ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf_blkptr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zdb_nicenum (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
dump_dsl_dataset(objset_t *os, uint64_t object, void *data, size_t size)
{
	dsl_dataset_phys_t *ds = data;
	time_t crtime;
	char used[32], compressed[32], uncompressed[32], unique[32];
	char blkbuf[BP_SPRINTF_LEN];

	/* make sure nicenum has enough space */
	CTASSERT(sizeof (used) >= NN_NUMBUF_SZ);
	CTASSERT(sizeof (compressed) >= NN_NUMBUF_SZ);
	CTASSERT(sizeof (uncompressed) >= NN_NUMBUF_SZ);
	CTASSERT(sizeof (unique) >= NN_NUMBUF_SZ);

	if (ds == NULL)
		return;

	ASSERT(size == sizeof (*ds));
	crtime = ds->ds_creation_time;
	zdb_nicenum(ds->ds_referenced_bytes, used, sizeof (used));
	zdb_nicenum(ds->ds_compressed_bytes, compressed, sizeof (compressed));
	zdb_nicenum(ds->ds_uncompressed_bytes, uncompressed,
	    sizeof (uncompressed));
	zdb_nicenum(ds->ds_unique_bytes, unique, sizeof (unique));
	snprintf_blkptr(blkbuf, sizeof (blkbuf), &ds->ds_bp);

	(void) printf("\t\tdir_obj = %llu\n",
	    (u_longlong_t)ds->ds_dir_obj);
	(void) printf("\t\tprev_snap_obj = %llu\n",
	    (u_longlong_t)ds->ds_prev_snap_obj);
	(void) printf("\t\tprev_snap_txg = %llu\n",
	    (u_longlong_t)ds->ds_prev_snap_txg);
	(void) printf("\t\tnext_snap_obj = %llu\n",
	    (u_longlong_t)ds->ds_next_snap_obj);
	(void) printf("\t\tsnapnames_zapobj = %llu\n",
	    (u_longlong_t)ds->ds_snapnames_zapobj);
	(void) printf("\t\tnum_children = %llu\n",
	    (u_longlong_t)ds->ds_num_children);
	(void) printf("\t\tuserrefs_obj = %llu\n",
	    (u_longlong_t)ds->ds_userrefs_obj);
	(void) printf("\t\tcreation_time = %s", ctime(&crtime));
	(void) printf("\t\tcreation_txg = %llu\n",
	    (u_longlong_t)ds->ds_creation_txg);
	(void) printf("\t\tdeadlist_obj = %llu\n",
	    (u_longlong_t)ds->ds_deadlist_obj);
	(void) printf("\t\tused_bytes = %s\n", used);
	(void) printf("\t\tcompressed_bytes = %s\n", compressed);
	(void) printf("\t\tuncompressed_bytes = %s\n", uncompressed);
	(void) printf("\t\tunique = %s\n", unique);
	(void) printf("\t\tfsid_guid = %llu\n",
	    (u_longlong_t)ds->ds_fsid_guid);
	(void) printf("\t\tguid = %llu\n",
	    (u_longlong_t)ds->ds_guid);
	(void) printf("\t\tflags = %llx\n",
	    (u_longlong_t)ds->ds_flags);
	(void) printf("\t\tnext_clones_obj = %llu\n",
	    (u_longlong_t)ds->ds_next_clones_obj);
	(void) printf("\t\tprops_obj = %llu\n",
	    (u_longlong_t)ds->ds_props_obj);
	(void) printf("\t\tbp = %s\n", blkbuf);
}