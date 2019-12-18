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
 int /*<<< orphan*/  SET_STA ; 
 int /*<<< orphan*/  USBA_FORCE_STALL ; 
 int /*<<< orphan*/  WAIT_FOR_SETUP ; 
 int /*<<< orphan*/  usba_ep_writel (struct usba_ep*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_protocol_stall(struct usba_udc *udc, struct usba_ep *ep)
{
	usba_ep_writel(ep, SET_STA, USBA_FORCE_STALL);
	ep->state = WAIT_FOR_SETUP;
}