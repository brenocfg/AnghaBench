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
struct inode {int dummy; } ;
struct file {struct debug_buffer* private_data; } ;
struct debug_buffer {int /*<<< orphan*/  output_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct debug_buffer*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int debug_close(struct inode *inode, struct file *file)
{
	struct debug_buffer *buf = file->private_data;

	if (buf) {
		vfree(buf->output_buf);
		kfree(buf);
	}

	return 0;
}