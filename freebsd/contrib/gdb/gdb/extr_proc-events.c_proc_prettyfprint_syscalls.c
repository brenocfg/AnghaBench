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
typedef  int /*<<< orphan*/  sysset_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_SYSCALLS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ prismember (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  proc_prettyfprint_syscall (int /*<<< orphan*/ *,int,int) ; 

void
proc_prettyfprint_syscalls (FILE *file, sysset_t *sysset, int verbose)
{
  int i;

  for (i = 0; i < MAX_SYSCALLS; i++)
    if (prismember (sysset, i))
      {
	proc_prettyfprint_syscall (file, i, verbose);
      }
  fprintf (file, "\n");
}