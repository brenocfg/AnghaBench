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
struct TYPE_2__ {int (* func ) () ;int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_COLOR_RED ; 
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perf_test__matches (int,int,char const**) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int stub1 () ; 
 TYPE_1__* tests ; 

__attribute__((used)) static int __cmd_test(int argc, const char *argv[])
{
	int i = 0;
	int width = 0;

	while (tests[i].func) {
		int len = strlen(tests[i].desc);

		if (width < len)
			width = len;
		++i;
	}

	i = 0;
	while (tests[i].func) {
		int curr = i++, err;

		if (!perf_test__matches(curr, argc, argv))
			continue;

		pr_info("%2d: %-*s:", i, width, tests[curr].desc);
		pr_debug("\n--- start ---\n");
		err = tests[curr].func();
		pr_debug("---- end ----\n%s:", tests[curr].desc);
		if (err)
			color_fprintf(stderr, PERF_COLOR_RED, " FAILED!\n");
		else
			pr_info(" Ok\n");
	}

	return 0;
}