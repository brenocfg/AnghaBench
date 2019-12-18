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
struct serio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEYBOARD_UNLOCK_REG ; 
 int /*<<< orphan*/  KEY_IRQ_ENABLE_REG ; 
 int /*<<< orphan*/  Q40_IRQ_KEYBOARD ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  master_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q40kbd_flush () ; 

__attribute__((used)) static void q40kbd_close(struct serio *port)
{
	master_outb(0, KEY_IRQ_ENABLE_REG);
	master_outb(-1, KEYBOARD_UNLOCK_REG);
	free_irq(Q40_IRQ_KEYBOARD, NULL);

	q40kbd_flush();
}