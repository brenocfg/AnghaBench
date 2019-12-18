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
struct pt_unit {int flags; int /*<<< orphan*/  available; int /*<<< orphan*/ * bufptr; } ;
struct inode {int dummy; } ;
struct file {struct pt_unit* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int PT_REWIND ; 
 int PT_WRITING ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pt_rewind (struct pt_unit*) ; 
 int /*<<< orphan*/  pt_write_fm (struct pt_unit*) ; 

__attribute__((used)) static int
pt_release(struct inode *inode, struct file *file)
{
	struct pt_unit *tape = file->private_data;

	if (atomic_read(&tape->available) > 1)
		return -EINVAL;

	if (tape->flags & PT_WRITING)
		pt_write_fm(tape);

	if (tape->flags & PT_REWIND)
		pt_rewind(tape);

	kfree(tape->bufptr);
	tape->bufptr = NULL;

	atomic_inc(&tape->available);

	return 0;

}