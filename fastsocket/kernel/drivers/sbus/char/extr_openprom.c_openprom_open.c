#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {void* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  current_node; int /*<<< orphan*/  lastnode; } ;
typedef  TYPE_1__ DATA ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  of_find_node_by_path (char*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int openprom_open(struct inode * inode, struct file * file)
{
	DATA *data;

	data = kmalloc(sizeof(DATA), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	lock_kernel();
	data->current_node = of_find_node_by_path("/");
	data->lastnode = data->current_node;
	file->private_data = (void *) data;
	unlock_kernel();

	return 0;
}