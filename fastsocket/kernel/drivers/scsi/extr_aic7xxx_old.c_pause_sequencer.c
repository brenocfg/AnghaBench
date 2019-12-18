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
struct aic7xxx_host {int features; int /*<<< orphan*/  pause; } ;

/* Variables and functions */
 int AHC_ULTRA2 ; 
 int /*<<< orphan*/  CCSCBCTL ; 
 int /*<<< orphan*/  HCNTRL ; 
 int PAUSE ; 
 int aic_inb (struct aic7xxx_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_outb (struct aic7xxx_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pause_sequencer(struct aic7xxx_host *p)
{
  aic_outb(p, p->pause, HCNTRL);
  while ((aic_inb(p, HCNTRL) & PAUSE) == 0)
  {
    ;
  }
  if(p->features & AHC_ULTRA2)
  {
    aic_inb(p, CCSCBCTL);
  }
}