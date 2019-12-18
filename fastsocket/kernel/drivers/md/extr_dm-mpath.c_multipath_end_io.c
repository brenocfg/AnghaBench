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
union map_info {struct dm_mpath_io* ptr; } ;
struct request {int dummy; } ;
struct pgpath {int /*<<< orphan*/  path; TYPE_1__* pg; } ;
struct path_selector {TYPE_2__* type; } ;
struct multipath {int dummy; } ;
struct dm_target {struct multipath* private; } ;
struct dm_mpath_io {int /*<<< orphan*/  nr_bytes; struct pgpath* pgpath; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* end_io ) (struct path_selector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct path_selector ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  clear_mapinfo (struct multipath*,union map_info*) ; 
 int do_end_io (struct multipath*,struct request*,int,struct dm_mpath_io*) ; 
 int /*<<< orphan*/  stub1 (struct path_selector*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int multipath_end_io(struct dm_target *ti, struct request *clone,
			    int error, union map_info *map_context)
{
	struct multipath *m = ti->private;
	struct dm_mpath_io *mpio = map_context->ptr;
	struct pgpath *pgpath;
	struct path_selector *ps;
	int r;

	BUG_ON(!mpio);

	r  = do_end_io(m, clone, error, mpio);
	pgpath = mpio->pgpath;
	if (pgpath) {
		ps = &pgpath->pg->ps;
		if (ps->type->end_io)
			ps->type->end_io(ps, &pgpath->path, mpio->nr_bytes);
	}
	clear_mapinfo(m, map_context);

	return r;
}