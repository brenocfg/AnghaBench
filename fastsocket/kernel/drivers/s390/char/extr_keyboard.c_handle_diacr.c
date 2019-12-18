#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kbd_data {int diacr; int accent_table_size; int /*<<< orphan*/  tty; TYPE_1__* accent_table; } ;
struct TYPE_2__ {int diacr; unsigned int base; unsigned int result; } ;

/* Variables and functions */
 int /*<<< orphan*/  kbd_put_queue (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int
handle_diacr(struct kbd_data *kbd, unsigned int ch)
{
	int i, d;

	d = kbd->diacr;
	kbd->diacr = 0;

	for (i = 0; i < kbd->accent_table_size; i++) {
		if (kbd->accent_table[i].diacr == d &&
		    kbd->accent_table[i].base == ch)
			return kbd->accent_table[i].result;
	}

	if (ch == ' ' || ch == d)
		return d;

	kbd_put_queue(kbd->tty, d);
	return ch;
}