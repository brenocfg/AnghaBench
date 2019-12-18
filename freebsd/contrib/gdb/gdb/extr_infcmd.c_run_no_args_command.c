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
 char* set_inferior_args (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static void
run_no_args_command (char *args, int from_tty)
{
  char *old_args = set_inferior_args (xstrdup (""));
  xfree (old_args);
}