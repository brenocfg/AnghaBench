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
struct inode {int dummy; } ;
struct file {struct rt2x00debug_intf* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2x00debug_file_release(struct inode *inode, struct file *file)
{
	struct rt2x00debug_intf *intf = file->private_data;

	module_put(intf->debug->owner);

	return 0;
}