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
struct seq_file {int /*<<< orphan*/  lock; int /*<<< orphan*/  version; int /*<<< orphan*/  read_pos; int /*<<< orphan*/  count; int /*<<< orphan*/  index; } ;
struct file {int /*<<< orphan*/  f_version; int /*<<< orphan*/  f_pos; scalar_t__ private_data; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  traverse (struct seq_file*,int /*<<< orphan*/ ) ; 

loff_t seq_lseek(struct file *file, loff_t offset, int origin)
{
	struct seq_file *m = (struct seq_file *)file->private_data;
	loff_t retval = -EINVAL;

	mutex_lock(&m->lock);
	m->version = file->f_version;
	switch (origin) {
		case 1:
			offset += file->f_pos;
		case 0:
			if (offset < 0)
				break;
			retval = offset;
			if (offset != m->read_pos) {
				while ((retval=traverse(m, offset)) == -EAGAIN)
					;
				if (retval) {
					/* with extreme prejudice... */
					file->f_pos = 0;
					m->read_pos = 0;
					m->version = 0;
					m->index = 0;
					m->count = 0;
				} else {
					m->read_pos = offset;
					retval = file->f_pos = offset;
				}
			}
	}
	file->f_version = m->version;
	mutex_unlock(&m->lock);
	return retval;
}