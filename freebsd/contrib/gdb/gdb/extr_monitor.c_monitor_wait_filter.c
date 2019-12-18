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
struct target_waitstatus {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int MO_PRINT_PROGRAM_OUTPUT ; 
 TYPE_1__* current_monitor ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 scalar_t__ monitor_debug_p ; 
 int monitor_expect_prompt (char*,int) ; 
 int /*<<< orphan*/  putchar_unfiltered (char) ; 
 scalar_t__ remote_debug ; 

__attribute__((used)) static void
monitor_wait_filter (char *buf,
		     int bufmax,
		     int *ext_resp_len,
		     struct target_waitstatus *status)
{
  int resp_len;
  do
    {
      resp_len = monitor_expect_prompt (buf, bufmax);
      *ext_resp_len = resp_len;

      if (resp_len <= 0)
	fprintf_unfiltered (gdb_stderr, "monitor_wait:  excessive response from monitor: %s.", buf);
    }
  while (resp_len < 0);

  /* Print any output characters that were preceded by ^O.  */
  /* FIXME - This would be great as a user settabgle flag */
  if (monitor_debug_p || remote_debug
      || current_monitor->flags & MO_PRINT_PROGRAM_OUTPUT)
    {
      int i;

      for (i = 0; i < resp_len - 1; i++)
	if (buf[i] == 0x0f)
	  putchar_unfiltered (buf[++i]);
    }
}