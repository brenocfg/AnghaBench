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
struct ftrace_buffer_info {scalar_t__ spare; TYPE_1__* tr; } ;
struct file {struct ftrace_buffer_info* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ftrace_buffer_info*) ; 
 int /*<<< orphan*/  ring_buffer_free_read_page (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tracing_buffers_release(struct inode *inode, struct file *file)
{
	struct ftrace_buffer_info *info = file->private_data;

	if (info->spare)
		ring_buffer_free_read_page(info->tr->buffer, info->spare);
	kfree(info);

	return 0;
}