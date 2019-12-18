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
struct selector {int /*<<< orphan*/  valid_paths; } ;
struct path_selector {scalar_t__ context; } ;
struct path_info {unsigned int repeat_count; int /*<<< orphan*/  list; struct dm_path* path; } ;
struct dm_path {struct path_info* pscontext; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int RR_MIN_IO ; 
 struct path_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sscanf (char*,char*,unsigned int*,char*) ; 

__attribute__((used)) static int rr_add_path(struct path_selector *ps, struct dm_path *path,
		       int argc, char **argv, char **error)
{
	struct selector *s = (struct selector *) ps->context;
	struct path_info *pi;
	unsigned repeat_count = RR_MIN_IO;
	char dummy;

	if (argc > 1) {
		*error = "round-robin ps: incorrect number of arguments";
		return -EINVAL;
	}

	/* First path argument is number of I/Os before switching path */
	if ((argc == 1) && (sscanf(argv[0], "%u%c", &repeat_count, &dummy) != 1)) {
		*error = "round-robin ps: invalid repeat count";
		return -EINVAL;
	}

	/* allocate the path */
	pi = kmalloc(sizeof(*pi), GFP_KERNEL);
	if (!pi) {
		*error = "round-robin ps: Error allocating path context";
		return -ENOMEM;
	}

	pi->path = path;
	pi->repeat_count = repeat_count;

	path->pscontext = pi;

	list_add_tail(&pi->list, &s->valid_paths);

	return 0;
}