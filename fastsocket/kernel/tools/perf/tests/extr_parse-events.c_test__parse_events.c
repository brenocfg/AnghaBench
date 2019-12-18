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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_EVENTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test__events ; 
 int /*<<< orphan*/  test__events_pmu ; 
 int /*<<< orphan*/  test__terms ; 
 scalar_t__ test_pmu () ; 
 int test_pmu_events () ; 
 int test_terms (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int test__parse_events(void)
{
	int ret1, ret2 = 0;

#define TEST_EVENTS(tests)				\
do {							\
	ret1 = test_events(tests, ARRAY_SIZE(tests));	\
	if (!ret2)					\
		ret2 = ret1;				\
} while (0)

	TEST_EVENTS(test__events);

	if (test_pmu())
		TEST_EVENTS(test__events_pmu);

	if (test_pmu()) {
		int ret = test_pmu_events();
		if (ret)
			return ret;
	}

	ret1 = test_terms(test__terms, ARRAY_SIZE(test__terms));
	if (!ret2)
		ret2 = ret1;

	return ret2;
}