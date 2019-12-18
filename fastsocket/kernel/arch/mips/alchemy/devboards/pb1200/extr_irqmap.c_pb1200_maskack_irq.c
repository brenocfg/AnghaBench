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
struct TYPE_2__ {int intclr_mask; int intclr; int int_status; } ;

/* Variables and functions */
 unsigned int PB1200_INT_BEGIN ; 
 int /*<<< orphan*/  au_sync () ; 
 TYPE_1__* bcsr ; 

__attribute__((used)) static void pb1200_maskack_irq(unsigned int irq_nr)
{
	bcsr->intclr_mask = 1 << (irq_nr - PB1200_INT_BEGIN);
	bcsr->intclr = 1 << (irq_nr - PB1200_INT_BEGIN);
	bcsr->int_status = 1 << (irq_nr - PB1200_INT_BEGIN);	/* ack */
	au_sync();
}