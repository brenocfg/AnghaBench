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
struct scsi_tape {scalar_t__ door_locked; scalar_t__ in_use; int /*<<< orphan*/  buffer; } ;
struct inode {int dummy; } ;
struct file {struct scsi_tape* private_data; } ;

/* Variables and functions */
 scalar_t__ ST_LOCKED_AUTO ; 
 int /*<<< orphan*/  do_door_lock (struct scsi_tape*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  normalize_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_tape_put (struct scsi_tape*) ; 
 int /*<<< orphan*/  st_dev_arr_lock ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int st_release(struct inode *inode, struct file *filp)
{
	int result = 0;
	struct scsi_tape *STp = filp->private_data;

	if (STp->door_locked == ST_LOCKED_AUTO)
		do_door_lock(STp, 0);

	normalize_buffer(STp->buffer);
	write_lock(&st_dev_arr_lock);
	STp->in_use = 0;
	write_unlock(&st_dev_arr_lock);
	scsi_tape_put(STp);

	return result;
}