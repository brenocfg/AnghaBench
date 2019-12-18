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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char** syscall_table ; 

void
proc_prettyfprint_syscall (FILE *file, int num, int verbose)
{
  if (syscall_table[num])
    fprintf (file, "SYS_%s ", syscall_table[num]);
  else
    fprintf (file, "<Unknown syscall %d> ", num);
}