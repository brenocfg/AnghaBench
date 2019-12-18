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
 int /*<<< orphan*/  INTMSK_UART3 ; 
 int /*<<< orphan*/  SUBMSK_UART3 ; 
 int /*<<< orphan*/  s3c_irqsub_mask (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c2443_irq_uart3_mask(unsigned int irqno)
{
	s3c_irqsub_mask(irqno, INTMSK_UART3, SUBMSK_UART3);
}