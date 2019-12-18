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
struct TYPE_2__ {int /*<<< orphan*/  stripes_to_set; int /*<<< orphan*/  stripes; } ;
struct raid_set {TYPE_1__ sc; } ;
typedef  enum raid_set_flags { ____Placeholder_raid_set_flags } raid_set_flags ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  STRIPES_MAX ; 
 int /*<<< orphan*/  STRIPES_MIN ; 
 int _absolute (char*,int,int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ range_ok (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  wake_do_raid (struct raid_set*) ; 

__attribute__((used)) static int sc_resize(struct raid_set *rs, int argc, char **argv,
		     enum raid_set_flags flag)
{
	int act, stripes;

	if (argc != 2)
		return -EINVAL;

	/* Deny permission in case the daemon is still resizing!. */
	if (atomic_read(&rs->sc.stripes_to_set))
		return -EPERM;

	if (sscanf(argv[1], "%d", &stripes) == 1 &&
	    stripes > 0) {
		act = atomic_read(&rs->sc.stripes);

		/* Make delta stripes absolute. */
		stripes = _absolute(argv[0], act, stripes);

		/*
		 * Check range and that the # of stripes changes.
		 * We leave the resizing to the wroker.
		 */
		if (range_ok(stripes, STRIPES_MIN, STRIPES_MAX) &&
		    stripes != atomic_read(&rs->sc.stripes)) {
			atomic_set(&rs->sc.stripes_to_set, stripes);
			wake_do_raid(rs);
			return 0;
		}
	}

	return -EINVAL;
}