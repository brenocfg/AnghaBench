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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_schedule_flip (struct tty_struct*) ; 

__attribute__((used)) static inline void
kbd_puts_queue(struct tty_struct *tty, char *cp)
{
	while (*cp)
		tty_insert_flip_char(tty, *cp++, 0);
	tty_schedule_flip(tty);
}