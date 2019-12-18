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
struct tpm_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  is_open; int /*<<< orphan*/  data_buffer; int /*<<< orphan*/  data_pending; int /*<<< orphan*/  user_read_timer; } ;
struct inode {int dummy; } ;
struct file {struct tpm_chip* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_singleshot_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 

int tpm_release(struct inode *inode, struct file *file)
{
	struct tpm_chip *chip = file->private_data;

	del_singleshot_timer_sync(&chip->user_read_timer);
	flush_scheduled_work();
	file->private_data = NULL;
	atomic_set(&chip->data_pending, 0);
	kfree(chip->data_buffer);
	clear_bit(0, &chip->is_open);
	put_device(chip->dev);
	return 0;
}