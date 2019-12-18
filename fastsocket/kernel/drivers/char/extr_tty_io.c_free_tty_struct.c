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
struct tty_struct {struct tty_struct* write_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_buffer_free_all (struct tty_struct*) ; 

void free_tty_struct(struct tty_struct *tty)
{
	kfree(tty->write_buf);
	tty_buffer_free_all(tty);
	kfree(tty);
}