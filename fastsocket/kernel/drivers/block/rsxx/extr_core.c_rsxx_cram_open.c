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
struct rsxx_cram {int /*<<< orphan*/  f_pos; int /*<<< orphan*/  i_private; } ;
struct inode {int /*<<< orphan*/  i_private; } ;
struct file {struct rsxx_cram* private_data; int /*<<< orphan*/  f_pos; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rsxx_cram* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsxx_cram_open(struct inode *inode, struct file *file)
{
	struct rsxx_cram *info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	info->i_private = inode->i_private;
	info->f_pos = file->f_pos;
	file->private_data = info;

	return 0;
}