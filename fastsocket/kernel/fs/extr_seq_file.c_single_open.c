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
struct seq_operations {int (* show ) (struct seq_file*,void*) ;int /*<<< orphan*/  stop; int /*<<< orphan*/  next; int /*<<< orphan*/  start; } ;
struct seq_file {void* private; } ;
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct seq_operations*) ; 
 struct seq_operations* kmalloc (int,int /*<<< orphan*/ ) ; 
 int seq_open (struct file*,struct seq_operations*) ; 
 int /*<<< orphan*/  single_next ; 
 int /*<<< orphan*/  single_start ; 
 int /*<<< orphan*/  single_stop ; 

int single_open(struct file *file, int (*show)(struct seq_file *, void *),
		void *data)
{
	struct seq_operations *op = kmalloc(sizeof(*op), GFP_KERNEL);
	int res = -ENOMEM;

	if (op) {
		op->start = single_start;
		op->next = single_next;
		op->stop = single_stop;
		op->show = show;
		res = seq_open(file, op);
		if (!res)
			((struct seq_file *)file->private_data)->private = data;
		else
			kfree(op);
	}
	return res;
}