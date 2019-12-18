#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct musb {int /*<<< orphan*/  mregs; TYPE_1__* gadget_driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MUSB_POWER ; 
 int /*<<< orphan*/  MUSB_POWER_SOFTCONN ; 
 int /*<<< orphan*/  musb_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void musb_pullup(struct musb *musb, int is_on)
{
	u8 power;

	power = musb_readb(musb->mregs, MUSB_POWER);
	if (is_on)
		power |= MUSB_POWER_SOFTCONN;
	else
		power &= ~MUSB_POWER_SOFTCONN;

	/* FIXME if on, HdrcStart; if off, HdrcStop */

	DBG(3, "gadget %s D+ pullup %s\n",
		musb->gadget_driver->function, is_on ? "on" : "off");
	musb_writeb(musb->mregs, MUSB_POWER, power);
}