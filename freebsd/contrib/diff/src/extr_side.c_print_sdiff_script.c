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
struct change {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  valid_lines; int /*<<< orphan*/  prefix_lines; } ;

/* Variables and functions */
 int /*<<< orphan*/  begin_output () ; 
 TYPE_1__* files ; 
 int /*<<< orphan*/  find_change ; 
 int /*<<< orphan*/  next0 ; 
 int /*<<< orphan*/  next1 ; 
 int /*<<< orphan*/  print_script (struct change*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_sdiff_common_lines (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_sdiff_hunk ; 

void
print_sdiff_script (struct change *script)
{
  begin_output ();

  next0 = next1 = - files[0].prefix_lines;
  print_script (script, find_change, print_sdiff_hunk);

  print_sdiff_common_lines (files[0].valid_lines, files[1].valid_lines);
}