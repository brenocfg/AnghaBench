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
struct i2c_client {int /*<<< orphan*/  adapter; } ;
struct file {struct i2c_client* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_put_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i2c_client*) ; 

__attribute__((used)) static int i2cdev_release(struct inode *inode, struct file *file)
{
	struct i2c_client *client = file->private_data;

	i2c_put_adapter(client->adapter);
	kfree(client);
	file->private_data = NULL;

	return 0;
}