#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ dds_guid; } ;
struct TYPE_19__ {scalar_t__ zfs_type; int /*<<< orphan*/  zfs_hdl; TYPE_1__ zfs_dmustats; } ;
typedef  TYPE_2__ zfs_handle_t ;
struct TYPE_20__ {struct TYPE_20__* next; TYPE_2__* zhp; } ;
typedef  TYPE_3__ iter_stack_frame_t ;
struct TYPE_21__ {int (* func ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; TYPE_3__* stack; scalar_t__ allowrecursion; int /*<<< orphan*/  first; } ;
typedef  TYPE_4__ iter_dependents_arg_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  EZFS_RECURSIVE ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 scalar_t__ ZFS_TYPE_BOOKMARK ; 
 scalar_t__ ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_close (TYPE_2__*) ; 
 int zfs_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_get_name (TYPE_2__*) ; 
 int zfs_iter_clones (TYPE_2__*,int (*) (TYPE_2__*,void*),TYPE_4__*) ; 
 int zfs_iter_filesystems (TYPE_2__*,int (*) (TYPE_2__*,void*),TYPE_4__*) ; 
 int zfs_iter_snapshots (TYPE_2__*,int /*<<< orphan*/ ,int (*) (TYPE_2__*,void*),TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iter_dependents_cb(zfs_handle_t *zhp, void *arg)
{
	iter_dependents_arg_t *ida = arg;
	int err = 0;
	boolean_t first = ida->first;
	ida->first = B_FALSE;

	if (zhp->zfs_type == ZFS_TYPE_SNAPSHOT) {
		err = zfs_iter_clones(zhp, iter_dependents_cb, ida);
	} else if (zhp->zfs_type != ZFS_TYPE_BOOKMARK) {
		iter_stack_frame_t isf;
		iter_stack_frame_t *f;

		/*
		 * check if there is a cycle by seeing if this fs is already
		 * on the stack.
		 */
		for (f = ida->stack; f != NULL; f = f->next) {
			if (f->zhp->zfs_dmustats.dds_guid ==
			    zhp->zfs_dmustats.dds_guid) {
				if (ida->allowrecursion) {
					zfs_close(zhp);
					return (0);
				} else {
					zfs_error_aux(zhp->zfs_hdl,
					    dgettext(TEXT_DOMAIN,
					    "recursive dependency at '%s'"),
					    zfs_get_name(zhp));
					err = zfs_error(zhp->zfs_hdl,
					    EZFS_RECURSIVE,
					    dgettext(TEXT_DOMAIN,
					    "cannot determine dependent "
					    "datasets"));
					zfs_close(zhp);
					return (err);
				}
			}
		}

		isf.zhp = zhp;
		isf.next = ida->stack;
		ida->stack = &isf;
		err = zfs_iter_filesystems(zhp, iter_dependents_cb, ida);
		if (err == 0) {
			err = zfs_iter_snapshots(zhp, B_FALSE,
			    iter_dependents_cb, ida, 0, 0);
		}
		ida->stack = isf.next;
	}

	if (!first && err == 0)
		err = ida->func(zhp, ida->data);
	else
		zfs_close(zhp);

	return (err);
}