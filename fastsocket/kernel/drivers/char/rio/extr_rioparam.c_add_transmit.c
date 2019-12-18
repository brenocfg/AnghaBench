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
struct Port {scalar_t__ TxAdd; scalar_t__ TxEnd; TYPE_1__* PhbP; int /*<<< orphan*/  Caddr; int /*<<< orphan*/ * TxStart; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_add; } ;

/* Variables and functions */
 int PKT_IN_USE ; 
 int /*<<< orphan*/  RIO_DEBUG_PARAM ; 
 int RIO_OFF (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int readw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rio_dprintk (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ *) ; 

void add_transmit(struct Port *PortP)
{
	if (readw(PortP->TxAdd) & PKT_IN_USE) {
		rio_dprintk(RIO_DEBUG_PARAM, "add_transmit: Packet has been stolen!");
	}
	writew(readw(PortP->TxAdd) | PKT_IN_USE, PortP->TxAdd);
	PortP->TxAdd = (PortP->TxAdd == PortP->TxEnd) ? PortP->TxStart : PortP->TxAdd + 1;
	writew(RIO_OFF(PortP->Caddr, PortP->TxAdd), &PortP->PhbP->tx_add);
}