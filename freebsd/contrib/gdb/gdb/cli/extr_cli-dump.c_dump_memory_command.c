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
 int /*<<< orphan*/  dump_memory_to_file (char*,char*,char*) ; 

__attribute__((used)) static void
dump_memory_command (char *cmd, char *mode)
{
  dump_memory_to_file (cmd, mode, "binary");
}