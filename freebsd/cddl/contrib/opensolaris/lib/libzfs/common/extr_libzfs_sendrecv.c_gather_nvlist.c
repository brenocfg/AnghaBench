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
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {char const* fsname; char const* fromsnap; char const* tosnap; int /*<<< orphan*/ * fss; void* replicate; void* verbose; void* recursive; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ send_data_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  void* boolean_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int EZFS_BADTYPE ; 
 int EZFS_NOMEM ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int ZFS_TYPE_VOLUME ; 
 int /*<<< orphan*/ * fsavl_create (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int send_iterate_fs (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static int
gather_nvlist(libzfs_handle_t *hdl, const char *fsname, const char *fromsnap,
    const char *tosnap, boolean_t recursive, boolean_t verbose,
    boolean_t replicate, nvlist_t **nvlp, avl_tree_t **avlp)
{
	zfs_handle_t *zhp;
	int error;
	uint64_t min_txg = 0, max_txg = 0;
	send_data_t sd = { 0 };

	zhp = zfs_open(hdl, fsname, ZFS_TYPE_FILESYSTEM | ZFS_TYPE_VOLUME);
	if (zhp == NULL)
		return (EZFS_BADTYPE);

	VERIFY(0 == nvlist_alloc(&sd.fss, NV_UNIQUE_NAME, 0));
	sd.fsname = fsname;
	sd.fromsnap = fromsnap;
	sd.tosnap = tosnap;
	sd.recursive = recursive;
	sd.verbose = verbose;
	sd.replicate = replicate;

	if ((error = send_iterate_fs(zhp, &sd)) != 0) {
		nvlist_free(sd.fss);
		if (avlp != NULL)
			*avlp = NULL;
		*nvlp = NULL;
		return (error);
	}

	if (avlp != NULL && (*avlp = fsavl_create(sd.fss)) == NULL) {
		nvlist_free(sd.fss);
		*nvlp = NULL;
		return (EZFS_NOMEM);
	}

	*nvlp = sd.fss;
	return (0);
}