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
struct aic7xxx_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_PULSE (struct aic7xxx_host*) ; 
 int /*<<< orphan*/  SEECTL ; 
 int /*<<< orphan*/  SEEMS ; 
 int SEERDY ; 
 int aic_inb (struct aic7xxx_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_outb (struct aic7xxx_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acquire_seeprom(struct aic7xxx_host *p)
{

  /*
   * Request access of the memory port.  When access is
   * granted, SEERDY will go high.  We use a 1 second
   * timeout which should be near 1 second more than
   * is needed.  Reason: after the 7870 chip reset, there
   * should be no contention.
   */
  aic_outb(p, SEEMS, SEECTL);
  CLOCK_PULSE(p);
  if ((aic_inb(p, SEECTL) & SEERDY) == 0)
  {
    aic_outb(p, 0, SEECTL);
    return (0);
  }
  return (1);
}