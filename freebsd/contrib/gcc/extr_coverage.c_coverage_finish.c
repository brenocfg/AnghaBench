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
 int /*<<< orphan*/  bbg_file_name ; 
 scalar_t__ bbg_file_opened ; 
 int /*<<< orphan*/  create_coverage () ; 
 int /*<<< orphan*/  da_file_name ; 
 int gcov_close () ; 
 int /*<<< orphan*/  local_tick ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void
coverage_finish (void)
{
  create_coverage ();
  if (bbg_file_opened)
    {
      int error = gcov_close ();

      if (error)
	unlink (bbg_file_name);
      if (!local_tick)
	/* Only remove the da file, if we cannot stamp it. If we can
	   stamp it, libgcov will DTRT.  */
	unlink (da_file_name);
    }
}