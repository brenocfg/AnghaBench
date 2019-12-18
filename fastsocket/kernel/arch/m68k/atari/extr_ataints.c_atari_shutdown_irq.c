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
 unsigned int IRQ_AUTO_4 ; 
 size_t VEC_INT4 ; 
 int /*<<< orphan*/  atari_disable_irq (unsigned int) ; 
 int /*<<< orphan*/  atari_turnoff_irq (unsigned int) ; 
 int /*<<< orphan*/  falcon_hblhandler ; 
 int /*<<< orphan*/  m68k_irq_shutdown (unsigned int) ; 
 int /*<<< orphan*/ * vectors ; 

__attribute__((used)) static void atari_shutdown_irq(unsigned int irq)
{
	atari_disable_irq(irq);
	atari_turnoff_irq(irq);
	m68k_irq_shutdown(irq);

	if (irq == IRQ_AUTO_4)
	    vectors[VEC_INT4] = falcon_hblhandler;
}