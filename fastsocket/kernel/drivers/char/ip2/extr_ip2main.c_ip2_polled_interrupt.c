#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* i2eBordStrPtr ;
struct TYPE_4__ {scalar_t__ i2eUsingIrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITRC_INTR ; 
 int /*<<< orphan*/  ITRC_NO_PORT ; 
 int /*<<< orphan*/  ITRC_RETURN ; 
 TYPE_1__** i2BoardPtrTable ; 
 int i2nBoards ; 
 int /*<<< orphan*/  ip2_irq_work (TYPE_1__*) ; 
 int /*<<< orphan*/  ip2trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  irq_counter ; 

__attribute__((used)) static void
ip2_polled_interrupt(void)
{
	int i;
	i2eBordStrPtr  pB;

	ip2trace(ITRC_NO_PORT, ITRC_INTR, 99, 1, 0);

	/* Service just the boards on the list using this irq */
	for( i = 0; i < i2nBoards; ++i ) {
		pB = i2BoardPtrTable[i];

//		Only process those boards which match our IRQ.
//			IRQ = 0 for polled boards, we won't poll "IRQ" boards

		if (pB && pB->i2eUsingIrq == 0)
			ip2_irq_work(pB);
	}

	++irq_counter;

	ip2trace (ITRC_NO_PORT, ITRC_INTR, ITRC_RETURN, 0 );
}