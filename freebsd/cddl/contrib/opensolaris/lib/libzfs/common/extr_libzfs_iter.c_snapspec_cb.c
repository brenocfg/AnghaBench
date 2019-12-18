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
typedef  int /*<<< orphan*/  zfs_handle_t ;
struct TYPE_2__ {int (* ssa_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ssa_arg; void* ssa_seenfirst; void* ssa_seenlast; int /*<<< orphan*/  ssa_last; int /*<<< orphan*/  ssa_first; } ;
typedef  TYPE_1__ snapspec_arg_t ;

/* Variables and functions */
 void* B_TRUE ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_get_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
snapspec_cb(zfs_handle_t *zhp, void *arg)
{
	snapspec_arg_t *ssa = arg;
	const char *shortsnapname;
	int err = 0;

	if (ssa->ssa_seenlast)
		return (0);

	shortsnapname = strchr(zfs_get_name(zhp), '@') + 1;
	if (!ssa->ssa_seenfirst && strcmp(shortsnapname, ssa->ssa_first) == 0)
		ssa->ssa_seenfirst = B_TRUE;
	if (strcmp(shortsnapname, ssa->ssa_last) == 0)
		ssa->ssa_seenlast = B_TRUE;

	if (ssa->ssa_seenfirst) {
		err = ssa->ssa_func(zhp, ssa->ssa_arg);
	} else {
		zfs_close(zhp);
	}

	return (err);
}