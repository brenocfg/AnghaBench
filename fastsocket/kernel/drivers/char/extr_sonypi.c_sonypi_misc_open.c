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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  open_count; int /*<<< orphan*/  fifo; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfifo_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ sonypi_device ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int sonypi_misc_open(struct inode *inode, struct file *file)
{
	lock_kernel();
	mutex_lock(&sonypi_device.lock);
	/* Flush input queue on first open */
	if (!sonypi_device.open_count)
		kfifo_reset(sonypi_device.fifo);
	sonypi_device.open_count++;
	mutex_unlock(&sonypi_device.lock);
	unlock_kernel();
	return 0;
}