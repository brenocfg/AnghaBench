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
struct path_selector {TYPE_1__* type; } ;
struct priority_group {int /*<<< orphan*/  pgpaths; struct path_selector ps; } ;
struct dm_target {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct path_selector*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dm_put_path_selector (TYPE_1__*) ; 
 int /*<<< orphan*/  free_pgpaths (int /*<<< orphan*/ *,struct dm_target*) ; 
 int /*<<< orphan*/  kfree (struct priority_group*) ; 
 int /*<<< orphan*/  stub1 (struct path_selector*) ; 

__attribute__((used)) static void free_priority_group(struct priority_group *pg,
				struct dm_target *ti)
{
	struct path_selector *ps = &pg->ps;

	if (ps->type) {
		ps->type->destroy(ps);
		dm_put_path_selector(ps->type);
	}

	free_pgpaths(&pg->pgpaths, ti);
	kfree(pg);
}