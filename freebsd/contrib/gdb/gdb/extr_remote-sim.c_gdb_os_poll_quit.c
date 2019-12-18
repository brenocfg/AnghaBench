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
typedef  int /*<<< orphan*/  host_callback ;

/* Variables and functions */
 scalar_t__ immediate_quit ; 
 scalar_t__ quit_flag ; 
 int /*<<< orphan*/  ui_loop_hook (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gdb_os_poll_quit (host_callback *p)
{
  if (ui_loop_hook != NULL)
    ui_loop_hook (0);

  if (quit_flag)		/* gdb's idea of quit */
    {
      quit_flag = 0;		/* we've stolen it */
      return 1;
    }
  else if (immediate_quit)
    {
      return 1;
    }
  return 0;
}