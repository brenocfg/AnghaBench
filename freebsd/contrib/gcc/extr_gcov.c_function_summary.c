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
struct TYPE_3__ {scalar_t__ calls; int /*<<< orphan*/  calls_executed; scalar_t__ branches; int /*<<< orphan*/  branches_taken; int /*<<< orphan*/  branches_executed; scalar_t__ lines; int /*<<< orphan*/  lines_executed; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ coverage_t ;

/* Variables and functions */
 scalar_t__ flag_branches ; 
 int /*<<< orphan*/  fnotice (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  format_gcov (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
function_summary (const coverage_t *coverage, const char *title)
{
  fnotice (stdout, "%s '%s'\n", title, coverage->name);

  if (coverage->lines)
    fnotice (stdout, "Lines executed:%s of %d\n",
	     format_gcov (coverage->lines_executed, coverage->lines, 2),
	     coverage->lines);
  else
    fnotice (stdout, "No executable lines\n");

  if (flag_branches)
    {
      if (coverage->branches)
	{
	  fnotice (stdout, "Branches executed:%s of %d\n",
		   format_gcov (coverage->branches_executed,
				coverage->branches, 2),
		   coverage->branches);
	  fnotice (stdout, "Taken at least once:%s of %d\n",
		   format_gcov (coverage->branches_taken,
				coverage->branches, 2),
		   coverage->branches);
	}
      else
	fnotice (stdout, "No branches\n");
      if (coverage->calls)
	fnotice (stdout, "Calls executed:%s of %d\n",
		 format_gcov (coverage->calls_executed, coverage->calls, 2),
		 coverage->calls);
      else
	fnotice (stdout, "No calls\n");
    }
}