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
struct tty_struct {int /*<<< orphan*/  termios_mutex; int /*<<< orphan*/  termios; } ;
struct ktermios {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct ktermios*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void copy_termios(struct tty_struct *tty, struct ktermios *kterm)
{
	mutex_lock(&tty->termios_mutex);
	memcpy(kterm, tty->termios, sizeof(struct ktermios));
	mutex_unlock(&tty->termios_mutex);
}