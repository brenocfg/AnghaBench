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
struct logger_reader {int /*<<< orphan*/  list; } ;
struct inode {int dummy; } ;
struct file {int f_mode; struct logger_reader* private_data; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int /*<<< orphan*/  kfree (struct logger_reader*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int logger_release(struct inode *ignored, struct file *file)
{
	if (file->f_mode & FMODE_READ) {
		struct logger_reader *reader = file->private_data;
		list_del(&reader->list);
		kfree(reader);
	}

	return 0;
}