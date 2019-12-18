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
 int /*<<< orphan*/  MENELAUS_INT_ACK1 ; 
 int /*<<< orphan*/  MENELAUS_INT_ACK2 ; 
 int menelaus_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int menelaus_ack_irq(int irq)
{
	if (irq > 7)
		return menelaus_write_reg(MENELAUS_INT_ACK2, 1 << (irq - 8));
	else
		return menelaus_write_reg(MENELAUS_INT_ACK1, 1 << irq);
}