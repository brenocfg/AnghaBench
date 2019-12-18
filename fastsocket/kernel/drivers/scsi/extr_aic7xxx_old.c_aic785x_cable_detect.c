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
 int BRDCS ; 
 int /*<<< orphan*/  BRDCTL ; 
 unsigned char BRDDAT5 ; 
 unsigned char BRDDAT6 ; 
 int BRDRW ; 
 int /*<<< orphan*/  CLOCK_PULSE (struct aic7xxx_host*) ; 
 int EEPROM ; 
 int /*<<< orphan*/  SPIOCAP ; 
 int aic_inb (struct aic7xxx_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_outb (struct aic7xxx_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aic785x_cable_detect(struct aic7xxx_host *p, int *int_50,
    int *ext_present, int *eeprom)
{
  unsigned char brdctl;

  aic_outb(p, BRDRW | BRDCS, BRDCTL);
  CLOCK_PULSE(p);
  aic_outb(p, 0, BRDCTL);
  CLOCK_PULSE(p);
  brdctl = aic_inb(p, BRDCTL);
  CLOCK_PULSE(p);
  *int_50 = !(brdctl & BRDDAT5);
  *ext_present = !(brdctl & BRDDAT6);
  *eeprom = (aic_inb(p, SPIOCAP) & EEPROM);
}