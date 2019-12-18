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
struct rt2x00debug_intf {TYPE_1__* debug; } ;
struct inode {struct rt2x00debug_intf* i_private; } ;
struct file {struct rt2x00debug_intf* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2x00debug_file_open(struct inode *inode, struct file *file)
{
	struct rt2x00debug_intf *intf = inode->i_private;

	file->private_data = inode->i_private;

	if (!try_module_get(intf->debug->owner))
		return -EBUSY;

	return 0;
}