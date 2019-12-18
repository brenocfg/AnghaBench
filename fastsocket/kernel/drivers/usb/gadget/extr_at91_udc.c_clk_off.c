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
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct at91_udc {int /*<<< orphan*/  iclk; int /*<<< orphan*/  fclk; TYPE_1__ gadget; scalar_t__ clocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clk_off(struct at91_udc *udc)
{
	if (!udc->clocked)
		return;
	udc->clocked = 0;
	udc->gadget.speed = USB_SPEED_UNKNOWN;
	clk_disable(udc->fclk);
	clk_disable(udc->iclk);
}