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
 int /*<<< orphan*/  OCD_RESET_RUN ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 int /*<<< orphan*/  error (char*) ; 
 int last_run_status ; 
 int /*<<< orphan*/  normal_stop () ; 
 int /*<<< orphan*/  ocd_desc ; 
 int /*<<< orphan*/  ocd_do_command (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  wait_for_inferior () ; 

__attribute__((used)) static void
bdm_restart_command (char *args, int from_tty)
{
  int status, pktlen;

  if (!ocd_desc)
    error ("Not connected to OCD device.");

  ocd_do_command (OCD_RESET_RUN, &status, &pktlen);
  last_run_status = status;
  clear_proceed_status ();
  wait_for_inferior ();
  normal_stop ();
}