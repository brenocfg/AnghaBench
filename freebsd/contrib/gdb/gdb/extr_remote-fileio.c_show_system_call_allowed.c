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
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*) ; 
 scalar_t__ remote_fio_system_call_allowed ; 

__attribute__((used)) static void
show_system_call_allowed (char *args, int from_tty)
{
  if (args)
    error ("Garbage after \"show remote system-call-allowed\" command: `%s'", args);
  printf_unfiltered ("Calling host system(3) call from target is %sallowed\n",
		     remote_fio_system_call_allowed ? "" : "not ");
}