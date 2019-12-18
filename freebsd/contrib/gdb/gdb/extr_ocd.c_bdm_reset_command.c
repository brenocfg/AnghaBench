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
 int /*<<< orphan*/  OCD_RESET ; 
 int /*<<< orphan*/  dcache_invalidate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  ocd_desc ; 
 int /*<<< orphan*/  ocd_do_command (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  registers_changed () ; 
 int /*<<< orphan*/  target_dcache ; 

__attribute__((used)) static void
bdm_reset_command (char *args, int from_tty)
{
  int status, pktlen;

  if (!ocd_desc)
    error ("Not connected to OCD device.");

  ocd_do_command (OCD_RESET, &status, &pktlen);
  dcache_invalidate (target_dcache);
  registers_changed ();
}