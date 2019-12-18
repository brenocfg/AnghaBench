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
struct tty_struct {int receive_room; int /*<<< orphan*/  flags; struct serport* disc_data; } ;
struct serport {int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; struct tty_struct* tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct serport* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int serport_ldisc_open(struct tty_struct *tty)
{
	struct serport *serport;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	serport = kzalloc(sizeof(struct serport), GFP_KERNEL);
	if (!serport)
		return -ENOMEM;

	serport->tty = tty;
	spin_lock_init(&serport->lock);
	init_waitqueue_head(&serport->wait);

	tty->disc_data = serport;
	tty->receive_room = 256;
	set_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);

	return 0;
}