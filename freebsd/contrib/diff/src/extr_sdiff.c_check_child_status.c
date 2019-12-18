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
 int INT_MAX ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int,char*,char const*,int) ; 
 int /*<<< orphan*/  exiterr () ; 

__attribute__((used)) static void
check_child_status (int werrno, int wstatus, int max_ok_status,
		    char const *subsidiary_program)
{
  int status = (! werrno && WIFEXITED (wstatus)
		? WEXITSTATUS (wstatus)
		: INT_MAX);

  if (max_ok_status < status)
    {
      error (0, werrno,
	     _(status == 126
	       ? "subsidiary program `%s' could not be invoked"
	       : status == 127
	       ? "subsidiary program `%s' not found"
	       : status == INT_MAX
	       ? "subsidiary program `%s' failed"
	       : "subsidiary program `%s' failed (exit status %d)"),
	     subsidiary_program, status);
      exiterr ();
    }
}