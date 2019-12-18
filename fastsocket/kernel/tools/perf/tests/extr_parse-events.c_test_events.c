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
struct test__event_st {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,unsigned int,int /*<<< orphan*/ ) ; 
 int test_event (struct test__event_st*) ; 

__attribute__((used)) static int test_events(struct test__event_st *events, unsigned cnt)
{
	int ret1, ret2 = 0;
	unsigned i;

	for (i = 0; i < cnt; i++) {
		struct test__event_st *e = &events[i];

		pr_debug("running test %d '%s'\n", i, e->name);
		ret1 = test_event(e);
		if (ret1)
			ret2 = ret1;
	}

	return ret2;
}