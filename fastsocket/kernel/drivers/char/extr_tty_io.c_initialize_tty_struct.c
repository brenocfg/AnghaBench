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
struct TYPE_2__ {int /*<<< orphan*/ * tail; int /*<<< orphan*/  head; } ;
struct tty_struct {int index; int /*<<< orphan*/  name; int /*<<< orphan*/  ops; struct tty_driver* driver; int /*<<< orphan*/  SAK_work; int /*<<< orphan*/  tty_files; int /*<<< orphan*/  ctrl_lock; int /*<<< orphan*/  read_lock; int /*<<< orphan*/  echo_lock; int /*<<< orphan*/  output_lock; int /*<<< orphan*/  atomic_write_lock; int /*<<< orphan*/  atomic_read_lock; int /*<<< orphan*/  hangup_work; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  ldisc_mutex; int /*<<< orphan*/  termios_mutex; TYPE_1__ buf; int /*<<< orphan*/  overrun_time; int /*<<< orphan*/ * pgrp; int /*<<< orphan*/ * session; int /*<<< orphan*/  magic; int /*<<< orphan*/  kref; } ;
struct tty_driver {int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TTY_MAGIC ; 
 int /*<<< orphan*/  do_SAK_work ; 
 int /*<<< orphan*/  do_tty_hangup ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tty_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_buffer_init (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_init (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_line_name (struct tty_driver*,int,int /*<<< orphan*/ ) ; 

void initialize_tty_struct(struct tty_struct *tty,
		struct tty_driver *driver, int idx)
{
	memset(tty, 0, sizeof(struct tty_struct));
	kref_init(&tty->kref);
	tty->magic = TTY_MAGIC;
	tty_ldisc_init(tty);
	tty->session = NULL;
	tty->pgrp = NULL;
	tty->overrun_time = jiffies;
	tty->buf.head = tty->buf.tail = NULL;
	tty_buffer_init(tty);
	mutex_init(&tty->termios_mutex);
	mutex_init(&tty->ldisc_mutex);
	init_waitqueue_head(&tty->write_wait);
	init_waitqueue_head(&tty->read_wait);
	INIT_WORK(&tty->hangup_work, do_tty_hangup);
	mutex_init(&tty->atomic_read_lock);
	mutex_init(&tty->atomic_write_lock);
	mutex_init(&tty->output_lock);
	mutex_init(&tty->echo_lock);
	spin_lock_init(&tty->read_lock);
	spin_lock_init(&tty->ctrl_lock);
	INIT_LIST_HEAD(&tty->tty_files);
	INIT_WORK(&tty->SAK_work, do_SAK_work);

	tty->driver = driver;
	tty->ops = driver->ops;
	tty->index = idx;
	tty_line_name(driver, idx, tty->name);
}