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

/* Variables and functions */
 scalar_t__ KS8695_INTST ; 
 scalar_t__ KS8695_IRQ_VA ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 

__attribute__((used)) static void ks8695_irq_ack(unsigned int irqno)
{
	__raw_writel((1 << irqno), KS8695_IRQ_VA + KS8695_INTST);
}