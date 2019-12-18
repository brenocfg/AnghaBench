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
struct file {scalar_t__ private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ alloc_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_registers_buffer ; 

__attribute__((used)) static int debug_registers_open(struct inode *inode, struct file *file)
{
	file->private_data = alloc_buffer(inode->i_private,
					  fill_registers_buffer);

	return file->private_data ? 0 : -ENOMEM;
}