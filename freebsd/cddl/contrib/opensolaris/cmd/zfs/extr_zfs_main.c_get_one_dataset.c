#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int zfs_type_t ;
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  scalar_t__ time_t ;
struct TYPE_3__ {TYPE_2__* ga_cbp; scalar_t__ ga_verbose; } ;
typedef  TYPE_1__ get_all_state_t ;
struct TYPE_4__ {scalar_t__ cb_used; scalar_t__ cb_alloc; } ;

/* Variables and functions */
 int CHECK_SPINNER ; 
 scalar_t__ SPINNER_TIME ; 
 int ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  libzfs_add_handle (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_progress (char*) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int zfs_get_type (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_iter_filesystems (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *,void*),void*) ; 

__attribute__((used)) static int
get_one_dataset(zfs_handle_t *zhp, void *data)
{
	static char *spin[] = { "-", "\\", "|", "/" };
	static int spinval = 0;
	static int spincheck = 0;
	static time_t last_spin_time = (time_t)0;
	get_all_state_t *state = data;
	zfs_type_t type = zfs_get_type(zhp);

	if (state->ga_verbose) {
		if (--spincheck < 0) {
			time_t now = time(NULL);
			if (last_spin_time + SPINNER_TIME < now) {
				update_progress(spin[spinval++ % 4]);
				last_spin_time = now;
			}
			spincheck = CHECK_SPINNER;
		}
	}

	/*
	 * Interate over any nested datasets.
	 */
	if (zfs_iter_filesystems(zhp, get_one_dataset, data) != 0) {
		zfs_close(zhp);
		return (1);
	}

	/*
	 * Skip any datasets whose type does not match.
	 */
	if ((type & ZFS_TYPE_FILESYSTEM) == 0) {
		zfs_close(zhp);
		return (0);
	}
	libzfs_add_handle(state->ga_cbp, zhp);
	assert(state->ga_cbp->cb_used <= state->ga_cbp->cb_alloc);

	return (0);
}