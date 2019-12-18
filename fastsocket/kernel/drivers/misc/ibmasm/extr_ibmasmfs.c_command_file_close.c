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
struct ibmasmfs_command_data {scalar_t__ command; } ;
struct file {struct ibmasmfs_command_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  command_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ibmasmfs_command_data*) ; 

__attribute__((used)) static int command_file_close(struct inode *inode, struct file *file)
{
	struct ibmasmfs_command_data *command_data = file->private_data;

	if (command_data->command)
		command_put(command_data->command);

	kfree(command_data);
	return 0;
}