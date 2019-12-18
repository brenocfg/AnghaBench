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
struct ipmi_file_private {int /*<<< orphan*/  fasync_queue; } ;
struct file {struct ipmi_file_private* private_data; } ;

/* Variables and functions */
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int ipmi_fasync(int fd, struct file *file, int on)
{
	struct ipmi_file_private *priv = file->private_data;
	int                      result;

	lock_kernel(); /* could race against open() otherwise */
	result = fasync_helper(fd, file, on, &priv->fasync_queue);
	unlock_kernel();

	return (result);
}