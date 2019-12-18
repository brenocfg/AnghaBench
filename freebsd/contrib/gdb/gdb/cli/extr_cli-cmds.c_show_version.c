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
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  immediate_quit ; 
 int /*<<< orphan*/  print_gdb_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 

__attribute__((used)) static void
show_version (char *args, int from_tty)
{
  immediate_quit++;
  print_gdb_version (gdb_stdout);
  printf_filtered ("\n");
  immediate_quit--;
}