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
typedef  int ushort ;
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kbd_put_queue (struct tty_struct*,int) ; 

__attribute__((used)) static void
to_utf8(struct tty_struct *tty, ushort c) 
{
	if (c < 0x80)
		/*  0******* */
		kbd_put_queue(tty, c);
	else if (c < 0x800) {
		/* 110***** 10****** */
		kbd_put_queue(tty, 0xc0 | (c >> 6));
		kbd_put_queue(tty, 0x80 | (c & 0x3f));
	} else {
		/* 1110**** 10****** 10****** */
		kbd_put_queue(tty, 0xe0 | (c >> 12));
		kbd_put_queue(tty, 0x80 | ((c >> 6) & 0x3f));
		kbd_put_queue(tty, 0x80 | (c & 0x3f));
	}
}