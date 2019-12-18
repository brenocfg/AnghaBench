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
 scalar_t__ bfd_get_mtime (scalar_t__) ; 
 scalar_t__ core_bfd ; 
 int /*<<< orphan*/  core_file_matches_executable_p (scalar_t__,scalar_t__) ; 
 scalar_t__ exec_bfd ; 
 int /*<<< orphan*/  warning (char*) ; 

void
validate_files (void)
{
  if (exec_bfd && core_bfd)
    {
      if (!core_file_matches_executable_p (core_bfd, exec_bfd))
	warning ("core file may not match specified executable file.");
      else if (bfd_get_mtime (exec_bfd) > bfd_get_mtime (core_bfd))
	warning ("exec file is newer than core file.");
    }
}