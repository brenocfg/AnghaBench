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
struct file {int /*<<< orphan*/ * private_data; } ;
struct capidev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  capidev_free (struct capidev*) ; 

__attribute__((used)) static int
capi_release(struct inode *inode, struct file *file)
{
	struct capidev *cdev = (struct capidev *)file->private_data;

	capidev_free(cdev);
	file->private_data = NULL;
	
	return 0;
}