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
struct ipmi_file_private {int /*<<< orphan*/  user; } ;
struct inode {int dummy; } ;
struct file {struct ipmi_file_private* private_data; } ;

/* Variables and functions */
 int ipmi_destroy_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ipmi_file_private*) ; 

__attribute__((used)) static int ipmi_release(struct inode *inode, struct file *file)
{
	struct ipmi_file_private *priv = file->private_data;
	int                      rv;

	rv = ipmi_destroy_user(priv->user);
	if (rv)
		return rv;

	/* FIXME - free the messages in the list. */
	kfree(priv);

	return 0;
}