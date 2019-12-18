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
struct inf {scalar_t__ stopped; } ;

/* Variables and functions */
 struct inf* active_inf () ; 
 int /*<<< orphan*/  check_empty (char*,char*) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*) ; 

__attribute__((used)) static void
show_stopped_cmd (char *args, int from_tty)
{
  struct inf *inf = active_inf ();
  check_empty (args, "show stopped");
  printf_unfiltered ("The inferior process %s stopped.\n",
		     inf->stopped ? "is" : "isn't");
}