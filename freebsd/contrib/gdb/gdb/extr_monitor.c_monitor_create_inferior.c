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
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exec_bfd ; 
 int first_time ; 
 int /*<<< orphan*/  proceed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
monitor_create_inferior (char *exec_file, char *args, char **env)
{
  if (args && (*args != '\000'))
    error ("Args are not supported by the monitor.");

  first_time = 1;
  clear_proceed_status ();
  proceed (bfd_get_start_address (exec_bfd), TARGET_SIGNAL_0, 0);
}