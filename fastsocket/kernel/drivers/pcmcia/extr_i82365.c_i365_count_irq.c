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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  I365_CSC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  debug (int,char*,int) ; 
 int /*<<< orphan*/  i365_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_hits ; 
 int /*<<< orphan*/  irq_sock ; 

__attribute__((used)) static irqreturn_t i365_count_irq(int irq, void *dev)
{
    i365_get(irq_sock, I365_CSC);
    irq_hits++;
    debug(2, "-> hit on irq %d\n", irq);
    return IRQ_HANDLED;
}