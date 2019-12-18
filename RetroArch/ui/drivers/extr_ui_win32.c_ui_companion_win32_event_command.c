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
typedef  enum event_command { ____Placeholder_event_command } event_command ;

/* Variables and functions */

__attribute__((used)) static void ui_companion_win32_event_command(
      void *data, enum event_command cmd)
{
   (void)data;
   (void)cmd;
}