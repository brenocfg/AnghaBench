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
struct logger_reader {int /*<<< orphan*/  mutex; int /*<<< orphan*/  readers; int /*<<< orphan*/  list; int /*<<< orphan*/  head; int /*<<< orphan*/  r_off; struct logger_reader* log; } ;
struct logger_log {int /*<<< orphan*/  mutex; int /*<<< orphan*/  readers; int /*<<< orphan*/  list; int /*<<< orphan*/  head; int /*<<< orphan*/  r_off; struct logger_log* log; } ;
struct inode {int /*<<< orphan*/  i_rdev; } ;
struct file {int f_mode; struct logger_reader* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int FMODE_READ ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 struct logger_reader* get_log_from_minor (int /*<<< orphan*/ ) ; 
 struct logger_reader* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 

__attribute__((used)) static int logger_open(struct inode *inode, struct file *file)
{
	struct logger_log *log;
	int ret;

	ret = nonseekable_open(inode, file);
	if (ret)
		return ret;

	log = get_log_from_minor(MINOR(inode->i_rdev));
	if (!log)
		return -ENODEV;

	if (file->f_mode & FMODE_READ) {
		struct logger_reader *reader;

		reader = kmalloc(sizeof(struct logger_reader), GFP_KERNEL);
		if (!reader)
			return -ENOMEM;

		reader->log = log;
		INIT_LIST_HEAD(&reader->list);

		mutex_lock(&log->mutex);
		reader->r_off = log->head;
		list_add_tail(&reader->list, &log->readers);
		mutex_unlock(&log->mutex);

		file->private_data = reader;
	} else
		file->private_data = log;

	return 0;
}