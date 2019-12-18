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
struct aic7xxx_host {int features; int chip; int flags; } ;

/* Variables and functions */
 int AHC_AIC7895 ; 
 int AHC_CHIPID_MASK ; 
 int AHC_CHNLB ; 
 int AHC_ULTRA2 ; 
 unsigned char BRDCS ; 
 int /*<<< orphan*/  BRDCTL ; 
 unsigned char BRDSTB ; 
 unsigned char BRDSTB_ULTRA2 ; 
 int /*<<< orphan*/  CLOCK_PULSE (struct aic7xxx_host*) ; 
 int /*<<< orphan*/  aic_outb (struct aic7xxx_host*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_brdctl (struct aic7xxx_host*) ; 

__attribute__((used)) static void
write_brdctl(struct aic7xxx_host *p, unsigned char value)
{
  unsigned char brdctl;

  /*
   * Make sure the SEEPROM is ready before we access it
   */
  CLOCK_PULSE(p);
  if (p->features & AHC_ULTRA2)
  {
    brdctl = value;
    aic_outb(p, brdctl, BRDCTL);
    CLOCK_PULSE(p);
    brdctl |= BRDSTB_ULTRA2;
    aic_outb(p, brdctl, BRDCTL);
    CLOCK_PULSE(p);
    brdctl &= ~BRDSTB_ULTRA2;
    aic_outb(p, brdctl, BRDCTL);
    CLOCK_PULSE(p);
    read_brdctl(p);
    CLOCK_PULSE(p);
  }
  else
  {
    brdctl = BRDSTB;
    if ( !((p->chip & AHC_CHIPID_MASK) == AHC_AIC7895) ||
          (p->flags & AHC_CHNLB) )
    {
      brdctl |= BRDCS;
    }
    brdctl = BRDSTB | BRDCS;
    aic_outb(p, brdctl, BRDCTL);
    CLOCK_PULSE(p);
    brdctl |= value;
    aic_outb(p, brdctl, BRDCTL);
    CLOCK_PULSE(p);
    brdctl &= ~BRDSTB;
    aic_outb(p, brdctl, BRDCTL);
    CLOCK_PULSE(p);
    brdctl &= ~BRDCS;
    aic_outb(p, brdctl, BRDCTL);
    CLOCK_PULSE(p);
  }
}