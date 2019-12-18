#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ciabase {unsigned char icr_data; int icr_mask; int int_mask; TYPE_1__* cia; } ;
struct TYPE_4__ {int intreq; } ;
struct TYPE_3__ {unsigned char icr; } ;

/* Variables and functions */
 unsigned char CIA_ICR_SETCLR ; 
 int IF_SETCLR ; 
 TYPE_2__ amiga_custom ; 

unsigned char cia_set_irq(struct ciabase *base, unsigned char mask)
{
	unsigned char old;

	old = (base->icr_data |= base->cia->icr);
	if (mask & CIA_ICR_SETCLR)
		base->icr_data |= mask;
	else
		base->icr_data &= ~mask;
	if (base->icr_data & base->icr_mask)
		amiga_custom.intreq = IF_SETCLR | base->int_mask;
	return old & base->icr_mask;
}