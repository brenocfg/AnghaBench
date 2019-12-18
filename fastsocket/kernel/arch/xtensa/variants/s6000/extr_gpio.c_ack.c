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
 unsigned int IRQ_BASE ; 
 scalar_t__ S6_GPIO_IC ; 
 scalar_t__ S6_REG_GPIO ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void ack(unsigned int irq)
{
	writeb(1 << (irq - IRQ_BASE), S6_REG_GPIO + S6_GPIO_IC);
}