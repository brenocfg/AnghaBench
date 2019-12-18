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
struct vme_master_resource {int /*<<< orphan*/  lock; scalar_t__ kern_base; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy_toio (scalar_t__,void*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

ssize_t ca91cx42_master_write(struct vme_master_resource *image, void *buf,
	size_t count, loff_t offset)
{
	int retval = 0;

	spin_lock(&(image->lock));

	memcpy_toio(image->kern_base + offset, buf, (unsigned int)count);
	retval = count;

	spin_unlock(&(image->lock));

	return retval;
}