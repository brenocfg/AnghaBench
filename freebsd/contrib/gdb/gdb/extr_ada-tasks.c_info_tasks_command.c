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
 int /*<<< orphan*/  info_task (char*,int) ; 
 int /*<<< orphan*/  info_tasks (char*,int) ; 

__attribute__((used)) static void
info_tasks_command (char *arg, int from_tty)
{
  if (arg == NULL || *arg == '\000')
    info_tasks (arg, from_tty);
  else
    info_task (arg, from_tty);
}