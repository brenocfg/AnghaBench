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
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int NSIG ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ prismember (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  proc_prettyfprint_signal (int /*<<< orphan*/ *,int,int) ; 

void
proc_prettyfprint_signalset (FILE *file, sigset_t *sigset, int verbose)
{
  int i;

  for (i = 0; i < NSIG; i++)
    if (prismember (sigset, i))
      proc_prettyfprint_signal (file, i, verbose);

  if (!verbose)
    fprintf (file, "\n");
}