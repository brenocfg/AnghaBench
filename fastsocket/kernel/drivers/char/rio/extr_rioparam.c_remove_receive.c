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
struct Port {scalar_t__ RxRemove; scalar_t__ RxEnd; TYPE_1__* PhbP; int /*<<< orphan*/  Caddr; int /*<<< orphan*/ * RxStart; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_remove; } ;

/* Variables and functions */
 int PKT_IN_USE ; 
 int RIO_OFF (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int readw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ *) ; 

void remove_receive(struct Port *PortP)
{
	writew(readw(PortP->RxRemove) & ~PKT_IN_USE, PortP->RxRemove);
	PortP->RxRemove = (PortP->RxRemove == PortP->RxEnd) ? PortP->RxStart : PortP->RxRemove + 1;
	writew(RIO_OFF(PortP->Caddr, PortP->RxRemove), &PortP->PhbP->rx_remove);
}