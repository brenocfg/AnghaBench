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
struct xenbus_watch {int dummy; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  balloon_set_new_target (unsigned long long) ; 
 int xenbus_scanf (int /*<<< orphan*/ ,char*,char*,char*,unsigned long long*) ; 

__attribute__((used)) static void watch_target(struct xenbus_watch *watch,
			 const char **vec, unsigned int len)
{
	unsigned long long new_target;
	int err;

	err = xenbus_scanf(XBT_NIL, "memory", "target", "%llu", &new_target);
	if (err != 1) {
		/* This is ok (for domain0 at least) - so just return */
		return;
	}

	/* The given memory/target value is in KiB, so it needs converting to
	 * pages. PAGE_SHIFT converts bytes to pages, hence PAGE_SHIFT - 10.
	 */
	balloon_set_new_target(new_target >> (PAGE_SHIFT - 10));
}