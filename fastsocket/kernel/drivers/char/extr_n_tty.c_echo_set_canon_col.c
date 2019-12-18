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
struct tty_struct {int /*<<< orphan*/  echo_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHO_OP_SET_CANON_COL ; 
 int /*<<< orphan*/  ECHO_OP_START ; 
 int /*<<< orphan*/  add_echo_byte (int /*<<< orphan*/ ,struct tty_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void echo_set_canon_col(struct tty_struct *tty)
{
	mutex_lock(&tty->echo_lock);

	add_echo_byte(ECHO_OP_START, tty);
	add_echo_byte(ECHO_OP_SET_CANON_COL, tty);

	mutex_unlock(&tty->echo_lock);
}