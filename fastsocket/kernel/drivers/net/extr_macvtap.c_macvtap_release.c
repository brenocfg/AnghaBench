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
struct macvtap_queue {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct macvtap_queue* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  macvtap_put_queue (struct macvtap_queue*) ; 

__attribute__((used)) static int macvtap_release(struct inode *inode, struct file *file)
{
	struct macvtap_queue *q = file->private_data;
	macvtap_put_queue(q);
	return 0;
}