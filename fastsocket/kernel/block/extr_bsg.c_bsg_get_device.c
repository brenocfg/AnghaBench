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
struct file {int dummy; } ;
struct bsg_device {int dummy; } ;
struct bsg_class_device {int /*<<< orphan*/  ref; int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct bsg_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct bsg_device*) ; 
 struct bsg_device* __bsg_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bsg_device* bsg_add_device (struct inode*,int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  bsg_kref_release_function ; 
 int /*<<< orphan*/  bsg_minor_idr ; 
 int /*<<< orphan*/  bsg_mutex ; 
 struct bsg_class_device* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bsg_device *bsg_get_device(struct inode *inode, struct file *file)
{
	struct bsg_device *bd;
	struct bsg_class_device *bcd;

	/*
	 * find the class device
	 */
	mutex_lock(&bsg_mutex);
	bcd = idr_find(&bsg_minor_idr, iminor(inode));
	if (bcd)
		kref_get(&bcd->ref);
	mutex_unlock(&bsg_mutex);

	if (!bcd)
		return ERR_PTR(-ENODEV);

	bd = __bsg_get_device(iminor(inode), bcd->queue);
	if (bd)
		return bd;

	bd = bsg_add_device(inode, bcd->queue, file);
	if (IS_ERR(bd))
		kref_put(&bcd->ref, bsg_kref_release_function);

	return bd;
}