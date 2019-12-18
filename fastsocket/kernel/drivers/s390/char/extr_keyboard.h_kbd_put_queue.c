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
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_schedule_flip (struct tty_struct*) ; 

__attribute__((used)) static inline void
kbd_put_queue(struct tty_struct *tty, int ch)
{
	tty_insert_flip_char(tty, ch, 0);
	tty_schedule_flip(tty);
}