#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int f_mode; int f_flags; scalar_t__ private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * rawbuf; } ;
struct TYPE_3__ {int /*<<< orphan*/ * rawbuf; } ;
struct au1550_state {int open_mode; int /*<<< orphan*/  open_wait; int /*<<< orphan*/  open_mutex; TYPE_2__ dma_adc; TYPE_1__ dma_dac; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  drain_dac (struct au1550_state*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stop_adc (struct au1550_state*) ; 
 int /*<<< orphan*/  stop_dac (struct au1550_state*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
au1550_release(struct inode *inode, struct file *file)
{
	struct au1550_state *s = (struct au1550_state *)file->private_data;

	lock_kernel();

	if (file->f_mode & FMODE_WRITE) {
		unlock_kernel();
		drain_dac(s, file->f_flags & O_NONBLOCK);
		lock_kernel();
	}

	mutex_lock(&s->open_mutex);
	if (file->f_mode & FMODE_WRITE) {
		stop_dac(s);
		kfree(s->dma_dac.rawbuf);
		s->dma_dac.rawbuf = NULL;
	}
	if (file->f_mode & FMODE_READ) {
		stop_adc(s);
		kfree(s->dma_adc.rawbuf);
		s->dma_adc.rawbuf = NULL;
	}
	s->open_mode &= ((~file->f_mode) & (FMODE_READ|FMODE_WRITE));
	mutex_unlock(&s->open_mutex);
	wake_up(&s->open_wait);
	unlock_kernel();
	return 0;
}