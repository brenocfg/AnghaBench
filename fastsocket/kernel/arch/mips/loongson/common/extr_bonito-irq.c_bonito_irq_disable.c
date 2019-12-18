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
 int BONITO_INTENCLR ; 
 unsigned int BONITO_IRQ_BASE ; 
 int /*<<< orphan*/  mmiowb () ; 

__attribute__((used)) static inline void bonito_irq_disable(unsigned int irq)
{
	BONITO_INTENCLR = (1 << (irq - BONITO_IRQ_BASE));
	mmiowb();
}