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
 int /*<<< orphan*/  enable_once_breakpoint ; 
 int /*<<< orphan*/  map_breakpoint_numbers (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enable_once_command (char *args, int from_tty)
{
  map_breakpoint_numbers (args, enable_once_breakpoint);
}