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
struct aic7xxx_host {int features; } ;

/* Variables and functions */
 int AHC_ULTRA2 ; 
 int ENSCSIRST ; 
 int SCSIRSTO ; 
 int /*<<< orphan*/  SCSISEQ ; 
 int /*<<< orphan*/  SIMODE1 ; 
 int /*<<< orphan*/  aic7xxx_clear_intstat (struct aic7xxx_host*) ; 
 int aic_inb (struct aic7xxx_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_outb (struct aic7xxx_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void
aic7xxx_reset_current_bus(struct aic7xxx_host *p)
{

  /* Disable reset interrupts. */
  aic_outb(p, aic_inb(p, SIMODE1) & ~ENSCSIRST, SIMODE1);

  /* Turn off the bus' current operations, after all, we shouldn't have any
   * valid commands left to cause a RSELI and SELO once we've tossed the
   * bus away with this reset, so we might as well shut down the sequencer
   * until the bus is restarted as oppossed to saving the current settings
   * and restoring them (which makes no sense to me). */

  /* Turn on the bus reset. */
  aic_outb(p, aic_inb(p, SCSISEQ) | SCSIRSTO, SCSISEQ);
  while ( (aic_inb(p, SCSISEQ) & SCSIRSTO) == 0)
    mdelay(5);

  /*
   * Some of the new Ultra2 chipsets need a longer delay after a chip
   * reset than just the init setup creates, so we have to delay here
   * before we go into a reset in order to make the chips happy.
   */
  if (p->features & AHC_ULTRA2)
    mdelay(250);
  else
    mdelay(50);

  /* Turn off the bus reset. */
  aic_outb(p, 0, SCSISEQ);
  mdelay(10);

  aic7xxx_clear_intstat(p);
  /* Re-enable reset interrupts. */
  aic_outb(p, aic_inb(p, SIMODE1) | ENSCSIRST, SIMODE1);

}