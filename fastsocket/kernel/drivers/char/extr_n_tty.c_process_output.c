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
struct tty_struct {int /*<<< orphan*/  output_lock; } ;

/* Variables and functions */
 int do_output_char (unsigned char,struct tty_struct*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tty_write_room (struct tty_struct*) ; 

__attribute__((used)) static int process_output(unsigned char c, struct tty_struct *tty)
{
	int	space, retval;

	mutex_lock(&tty->output_lock);

	space = tty_write_room(tty);
	retval = do_output_char(c, tty, space);

	mutex_unlock(&tty->output_lock);
	if (retval < 0)
		return -1;
	else
		return 0;
}