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
struct usba_udc {int dummy; } ;
struct usba_ep {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_ENB ; 
 int /*<<< orphan*/  SET_STA ; 
 int /*<<< orphan*/  STATUS_STAGE_IN ; 
 int /*<<< orphan*/  USBA_TX_COMPLETE ; 
 int /*<<< orphan*/  USBA_TX_PK_RDY ; 
 int /*<<< orphan*/  usba_ep_writel (struct usba_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_status(struct usba_udc *udc, struct usba_ep *ep)
{
	ep->state = STATUS_STAGE_IN;
	usba_ep_writel(ep, SET_STA, USBA_TX_PK_RDY);
	usba_ep_writel(ep, CTL_ENB, USBA_TX_COMPLETE);
}