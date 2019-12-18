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
struct kbd_data {int /*<<< orphan*/  tty; scalar_t__ diacr; } ;

/* Variables and functions */
 unsigned char handle_diacr (struct kbd_data*,unsigned char) ; 
 int /*<<< orphan*/  kbd_put_queue (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void
k_self(struct kbd_data *kbd, unsigned char value)
{
	if (kbd->diacr)
		value = handle_diacr(kbd, value);
	kbd_put_queue(kbd->tty, value);
}