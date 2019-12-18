#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct change {int ignore; struct change* link; } ;
struct TYPE_4__ {int /*<<< orphan*/  prefix_lines; } ;
struct TYPE_3__ {scalar_t__ fastmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIN_MAX ; 
 TYPE_2__* files ; 
 int /*<<< orphan*/  find_function_last_match ; 
 int /*<<< orphan*/  find_function_last_search ; 
 int /*<<< orphan*/  find_hunk ; 
 scalar_t__ ignore_blank_lines ; 
 TYPE_1__ ignore_regexp ; 
 int /*<<< orphan*/  mark_ignorable (struct change*) ; 
 int /*<<< orphan*/  pr_context_hunk ; 
 int /*<<< orphan*/  pr_unidiff_hunk ; 
 int /*<<< orphan*/  print_script (struct change*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
print_context_script (struct change *script, bool unidiff)
{
  if (ignore_blank_lines || ignore_regexp.fastmap)
    mark_ignorable (script);
  else
    {
      struct change *e;
      for (e = script; e; e = e->link)
	e->ignore = false;
    }

  find_function_last_search = - files[0].prefix_lines;
  find_function_last_match = LIN_MAX;

  if (unidiff)
    print_script (script, find_hunk, pr_unidiff_hunk);
  else
    print_script (script, find_hunk, pr_context_hunk);
}