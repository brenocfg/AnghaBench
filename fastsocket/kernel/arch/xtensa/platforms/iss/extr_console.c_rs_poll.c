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
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 scalar_t__ SERIAL_TIMER_VALUE ; 
 int /*<<< orphan*/  SYS_read ; 
 int /*<<< orphan*/  SYS_select_one ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 unsigned long XTISS_SELECT_ONE_READ ; 
 scalar_t__ __simc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  serial_timer ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_lock ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rs_poll(unsigned long priv)
{
	struct tty_struct* tty = (struct tty_struct*) priv;

	struct timeval tv = { .tv_sec = 0, .tv_usec = 0 };
	int i = 0;
	unsigned char c;

	spin_lock(&timer_lock);

	while (__simc(SYS_select_one, 0, XTISS_SELECT_ONE_READ, (int)&tv,0,0)){
		__simc (SYS_read, 0, (unsigned long)&c, 1, 0, 0);
		tty_insert_flip_char(tty, c, TTY_NORMAL);
		i++;
	}

	if (i)
		tty_flip_buffer_push(tty);


	mod_timer(&serial_timer, jiffies + SERIAL_TIMER_VALUE);
	spin_unlock(&timer_lock);
}