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
struct usbtmc_device_data {int /*<<< orphan*/  kref; } ;
struct inode {int dummy; } ;
struct file {struct usbtmc_device_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbtmc_delete ; 

__attribute__((used)) static int usbtmc_release(struct inode *inode, struct file *file)
{
	struct usbtmc_device_data *data = file->private_data;

	kref_put(&data->kref, usbtmc_delete);
	return 0;
}