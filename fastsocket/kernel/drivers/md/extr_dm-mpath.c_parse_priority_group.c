#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct priority_group {unsigned int nr_pgpaths; int /*<<< orphan*/  pgpaths; int /*<<< orphan*/  ps; struct multipath* m; } ;
struct pgpath {int /*<<< orphan*/  list; struct priority_group* pg; } ;
struct multipath {struct dm_target* ti; } ;
struct dm_target {char* error; } ;
struct dm_arg_set {int argc; int /*<<< orphan*/  argv; } ;
struct dm_arg {int member_0; int member_1; char* member_2; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct priority_group* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct pgpath*) ; 
 int PTR_ERR (struct pgpath*) ; 
 struct priority_group* alloc_priority_group () ; 
 int /*<<< orphan*/  dm_consume_args (struct dm_arg_set*,unsigned int) ; 
 int dm_read_arg (struct dm_arg*,struct dm_arg_set*,unsigned int*,char**) ; 
 int /*<<< orphan*/  free_priority_group (struct priority_group*,struct dm_target*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pgpath* parse_path (struct dm_arg_set*,int /*<<< orphan*/ *,struct dm_target*) ; 
 int parse_path_selector (struct dm_arg_set*,struct priority_group*,struct dm_target*) ; 

__attribute__((used)) static struct priority_group *parse_priority_group(struct dm_arg_set *as,
						   struct multipath *m)
{
	static struct dm_arg _args[] = {
		{1, 1024, "invalid number of paths"},
		{0, 1024, "invalid number of selector args"}
	};

	int r;
	unsigned i, nr_selector_args, nr_args;
	struct priority_group *pg;
	struct dm_target *ti = m->ti;

	if (as->argc < 2) {
		as->argc = 0;
		ti->error = "not enough priority group arguments";
		return ERR_PTR(-EINVAL);
	}

	pg = alloc_priority_group();
	if (!pg) {
		ti->error = "couldn't allocate priority group";
		return ERR_PTR(-ENOMEM);
	}
	pg->m = m;

	r = parse_path_selector(as, pg, ti);
	if (r)
		goto bad;

	/*
	 * read the paths
	 */
	r = dm_read_arg(_args, as, &pg->nr_pgpaths, &ti->error);
	if (r)
		goto bad;

	r = dm_read_arg(_args + 1, as, &nr_selector_args, &ti->error);
	if (r)
		goto bad;

	nr_args = 1 + nr_selector_args;
	for (i = 0; i < pg->nr_pgpaths; i++) {
		struct pgpath *pgpath;
		struct dm_arg_set path_args;

		if (as->argc < nr_args) {
			ti->error = "not enough path parameters";
			r = -EINVAL;
			goto bad;
		}

		path_args.argc = nr_args;
		path_args.argv = as->argv;

		pgpath = parse_path(&path_args, &pg->ps, ti);
		if (IS_ERR(pgpath)) {
			r = PTR_ERR(pgpath);
			goto bad;
		}

		pgpath->pg = pg;
		list_add_tail(&pgpath->list, &pg->pgpaths);
		dm_consume_args(as, nr_args);
	}

	return pg;

 bad:
	free_priority_group(pg, ti);
	return ERR_PTR(r);
}