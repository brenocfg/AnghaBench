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
struct inf {scalar_t__ default_thread_run_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_empty (char*,char*) ; 
 struct inf* cur_inf () ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*) ; 

__attribute__((used)) static void
show_thread_default_run_cmd (char *args, int from_tty)
{
  struct inf *inf = cur_inf ();
  check_empty (args, "show thread default run");
  printf_unfiltered ("New threads %s allowed to run.\n",
		     inf->default_thread_run_sc == 0 ? "are" : "aren't");
}