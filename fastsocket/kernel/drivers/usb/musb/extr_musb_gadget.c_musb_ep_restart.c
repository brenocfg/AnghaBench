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
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct musb_request {scalar_t__ tx; int /*<<< orphan*/  epnum; TYPE_1__ request; } ;
struct musb {int /*<<< orphan*/  mregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_ep_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxstate (struct musb*,struct musb_request*) ; 
 int /*<<< orphan*/  txstate (struct musb*,struct musb_request*) ; 

__attribute__((used)) static void musb_ep_restart(struct musb *musb, struct musb_request *req)
{
	DBG(3, "<== %s request %p len %u on hw_ep%d\n",
		req->tx ? "TX/IN" : "RX/OUT",
		&req->request, req->request.length, req->epnum);

	musb_ep_select(musb->mregs, req->epnum);
	if (req->tx)
		txstate(musb, req);
	else
		rxstate(musb, req);
}