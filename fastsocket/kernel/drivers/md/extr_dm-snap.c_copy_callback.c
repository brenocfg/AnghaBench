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
struct dm_snapshot {TYPE_2__* store; } ;
struct dm_snap_pending_exception {int /*<<< orphan*/  e; struct dm_snapshot* snap; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* commit_exception ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dm_snap_pending_exception*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  commit_callback ; 
 int /*<<< orphan*/  pending_complete (struct dm_snap_pending_exception*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dm_snap_pending_exception*) ; 

__attribute__((used)) static void copy_callback(int read_err, unsigned long write_err, void *context)
{
	struct dm_snap_pending_exception *pe = context;
	struct dm_snapshot *s = pe->snap;

	if (read_err || write_err)
		pending_complete(pe, 0);

	else
		/* Update the metadata if we are persistent */
		s->store->type->commit_exception(s->store, &pe->e,
						 commit_callback, pe);
}