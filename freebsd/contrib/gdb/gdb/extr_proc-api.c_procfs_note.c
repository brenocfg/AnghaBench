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
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,char*,...) ; 
 scalar_t__ info_verbose ; 
 int /*<<< orphan*/  prepare_to_trace () ; 
 scalar_t__ procfs_file ; 
 scalar_t__ procfs_trace ; 
 scalar_t__ stdout ; 

void
procfs_note (char *msg, char *file, int line)
{
  prepare_to_trace ();
  if (procfs_trace)
    {
      if (info_verbose)
	fprintf (procfs_file ? procfs_file : stdout, 
		 "%s:%d -- ", file, line);
      fprintf (procfs_file ? procfs_file : stdout, "%s", msg);
      if (procfs_file)
	fflush (procfs_file);
    }
}