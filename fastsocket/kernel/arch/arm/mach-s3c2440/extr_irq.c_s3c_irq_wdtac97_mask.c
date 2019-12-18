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
 int /*<<< orphan*/  INTMSK_WDT ; 
 int /*<<< orphan*/  s3c_irqsub_mask (unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
s3c_irq_wdtac97_mask(unsigned int irqno)
{
	s3c_irqsub_mask(irqno, INTMSK_WDT, 3<<13);
}