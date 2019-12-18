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
struct TYPE_2__ {int /*<<< orphan*/  detach_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_empty (char*,char*) ; 
 TYPE_1__* cur_inf () ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
show_task_detach_sc_cmd (char *args, int from_tty)
{
  check_empty (args, "show task detach-suspend-count");
  printf_unfiltered ("The inferior task will be left with a suspend count of %d when detaching.\n",
		     cur_inf ()->detach_sc);
}