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
struct moxa_port {int /*<<< orphan*/  tableAddr; } ;

/* Variables and functions */
 int CTS_FlowCtl ; 
 int /*<<< orphan*/  FC_SetFlowCtl ; 
 int IXM_IXANY ; 
 int RTS_FlowCtl ; 
 int Rx_FlowCtl ; 
 int Tx_FlowCtl ; 
 int /*<<< orphan*/  moxafunc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void MoxaPortFlowCtrl(struct moxa_port *port, int rts, int cts,
		int txflow, int rxflow, int txany)
{
	int mode = 0;

	if (rts)
		mode |= RTS_FlowCtl;
	if (cts)
		mode |= CTS_FlowCtl;
	if (txflow)
		mode |= Tx_FlowCtl;
	if (rxflow)
		mode |= Rx_FlowCtl;
	if (txany)
		mode |= IXM_IXANY;
	moxafunc(port->tableAddr, FC_SetFlowCtl, mode);
}