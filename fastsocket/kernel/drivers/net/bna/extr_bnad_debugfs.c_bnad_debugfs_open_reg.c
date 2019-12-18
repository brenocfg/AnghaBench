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
struct inode {int /*<<< orphan*/  i_private; } ;
struct file {struct bnad_debug_info* private_data; } ;
struct bnad_debug_info {int /*<<< orphan*/  i_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct bnad_debug_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnad_debugfs_open_reg(struct inode *inode, struct file *file)
{
	struct bnad_debug_info *reg_debug;

	reg_debug = kzalloc(sizeof(struct bnad_debug_info), GFP_KERNEL);
	if (!reg_debug)
		return -ENOMEM;

	reg_debug->i_private = inode->i_private;

	file->private_data = reg_debug;

	return 0;
}