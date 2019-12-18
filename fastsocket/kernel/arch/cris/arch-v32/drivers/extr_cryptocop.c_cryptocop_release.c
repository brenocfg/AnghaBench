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
struct file {struct cryptocop_private* private_data; } ;
struct cryptocop_private {scalar_t__ sid; struct cryptocop_private* next; } ;

/* Variables and functions */
 scalar_t__ CRYPTOCOP_SESSION_ID_NONE ; 
 int /*<<< orphan*/  cryptocop_free_session (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct cryptocop_private*) ; 

__attribute__((used)) static int cryptocop_release(struct inode *inode, struct file *filp)
{
	struct cryptocop_private *dev = filp->private_data;
	struct cryptocop_private *dev_next;

	while (dev){
		dev_next = dev->next;
		if (dev->sid != CRYPTOCOP_SESSION_ID_NONE) {
			(void)cryptocop_free_session(dev->sid);
		}
		kfree(dev);
		dev = dev_next;
	}

	return 0;
}