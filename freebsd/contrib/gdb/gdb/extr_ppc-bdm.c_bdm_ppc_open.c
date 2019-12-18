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
typedef  int CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  OCD_TARGET_MOTO_PPC ; 
 int /*<<< orphan*/  bdm_ppc_ops ; 
 int /*<<< orphan*/  nowatchdog ; 
 int /*<<< orphan*/  ocd_open (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocd_write_bdm_register (int,int) ; 
 int /*<<< orphan*/  ocd_write_bytes (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bdm_ppc_open (char *name, int from_tty)
{
  CORE_ADDR watchdogaddr = 0xff000004;

  ocd_open (name, from_tty, OCD_TARGET_MOTO_PPC, &bdm_ppc_ops);

  /* We want interrupts to drop us into debugging mode. */
  /* Modify the DER register to accomplish this. */
  ocd_write_bdm_register (149, 0x20024000);

  /* Disable watchdog timer on the board */
  ocd_write_bytes (watchdogaddr, nowatchdog, 4);
}