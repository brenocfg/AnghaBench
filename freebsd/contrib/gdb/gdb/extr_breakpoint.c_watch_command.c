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
 int /*<<< orphan*/  hw_write ; 
 int /*<<< orphan*/  watch_command_1 (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
watch_command (char *arg, int from_tty)
{
  watch_command_1 (arg, hw_write, from_tty);
}