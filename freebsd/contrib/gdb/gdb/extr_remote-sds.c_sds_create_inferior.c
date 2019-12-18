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
 int /*<<< orphan*/  TARGET_SIGNAL_0 ; 
 int /*<<< orphan*/  bfd_get_start_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 int /*<<< orphan*/  exec_bfd ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  proceed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sds_create_inferior (char *exec_file, char *args, char **env)
{
  inferior_ptid = pid_to_ptid (42000);

  /* Clean up from the last time we were running.  */
  clear_proceed_status ();

  /* Let the remote process run.  */
  proceed (bfd_get_start_address (exec_bfd), TARGET_SIGNAL_0, 0);
}