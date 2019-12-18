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
struct qe_ep {int epnum; TYPE_1__* udc; } ;
struct TYPE_2__ {scalar_t__ soc_type; } ;

/* Variables and functions */
 int CPM_USB_EP_SHIFT ; 
 int CPM_USB_STOP_TX ; 
 int /*<<< orphan*/  CPM_USB_STOP_TX_OPCODE ; 
 scalar_t__ PORT_CPM ; 
 int /*<<< orphan*/  QE_CR_SUBBLOCK_USB ; 
 int /*<<< orphan*/  QE_USB_STOP_TX ; 
 int /*<<< orphan*/  cpm_command (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qe_issue_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qe_ep_cmd_stoptx(struct qe_ep *ep)
{
	if (ep->udc->soc_type == PORT_CPM)
		cpm_command(CPM_USB_STOP_TX | (ep->epnum << CPM_USB_EP_SHIFT),
				CPM_USB_STOP_TX_OPCODE);
	else
		qe_issue_cmd(QE_USB_STOP_TX, QE_CR_SUBBLOCK_USB,
				ep->epnum, 0);

	return 0;
}