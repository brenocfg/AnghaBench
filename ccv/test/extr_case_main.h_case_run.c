#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* dir; char* name; int /*<<< orphan*/  (* func ) (char*,int*) ;} ;
typedef  TYPE_1__ case_t ;

/* Variables and functions */
 scalar_t__ case_print_hi (char*,char const* const) ; 
 int /*<<< orphan*/  chdir (scalar_t__*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (scalar_t__*,char*) ; 
 int /*<<< orphan*/  stub1 (char*,int*) ; 

__attribute__((used)) static void case_run(case_t* test_case, const char* const match_test, int i, int total, int* pass, int* skip, int* fail)
{
	// Change the current directory.
	if (test_case->dir && test_case->dir[0] != 0 && strcmp(test_case->dir, ".") != 0)
		chdir(test_case->dir);
	int clr = 0;
	if (isatty(fileno(stdout)))
	{
		clr += printf("\033[0;34m[%d/%d]\033[0;0m \033[1;33m[RUN]\033[0;0m ", i + 1, total);
		clr += case_print_hi(test_case->name, match_test);
		clr += printf(" ...");
	} else
		clr += printf("[%d/%d] [RUN] %s ...", i + 1, total, test_case->name);
	fflush(stdout);
	int result = 0;
	test_case->func(test_case->name, &result);
	if (result == 0)
	{
		(*pass)++;
		for (; clr > 0; --clr)
			printf("\b");
		if (isatty(fileno(stdout)))
		{
			printf("\r\033[0;34m[%d/%d]\033[0;0m \033[1;32m[PASS]\033[0;0m ", i + 1, total);
			case_print_hi(test_case->name, match_test);
			printf("    \n");
		} else
			printf("\r[%d/%d] [PASS] %s    \n", i + 1, total, test_case->name);
	} else if (result == -2) {
		(*skip)++;
		if (isatty(fileno(stdout)))
		{
			printf("\n\033[0;34m[%d/%d]\033[0;0m \033[1;32m[SKIP]\033[0;0m ", i + 1, total);
			case_print_hi(test_case->name, match_test);
			printf("\n");
		} else
			printf("\n[%d/%d] [SKIP] %s\n", i + 1, total, test_case->name);
	} else {
		(*fail)++;
		if (isatty(fileno(stdout)))
		{
			printf("\n\033[0;34m[%d/%d]\033[0;0m \033[1;31m[FAIL]\033[0;0m ", i + 1, total);
			case_print_hi(test_case->name, match_test);
			printf("\n");
		} else
			printf("\n[%d/%d] [FAIL] %s\n", i + 1, total, test_case->name);
	}
}