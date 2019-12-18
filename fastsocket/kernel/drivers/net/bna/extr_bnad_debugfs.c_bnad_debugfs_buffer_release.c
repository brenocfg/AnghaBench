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
struct file {struct bnad_debug_info* private_data; } ;
struct bnad_debug_info {struct bnad_debug_info* debug_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct bnad_debug_info*) ; 

__attribute__((used)) static int
bnad_debugfs_buffer_release(struct inode *inode, struct file *file)
{
	struct bnad_debug_info *debug = file->private_data;

	if (!debug)
		return 0;

	kfree(debug->debug_buffer);

	file->private_data = NULL;
	kfree(debug);
	debug = NULL;
	return 0;
}