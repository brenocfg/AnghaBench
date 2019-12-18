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
struct uio_device {int minor; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_ID_MASK ; 
 int idr_get_new (int /*<<< orphan*/ *,struct uio_device*,int*) ; 
 scalar_t__ idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  minor_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_idr ; 

__attribute__((used)) static int uio_get_minor(struct uio_device *idev)
{
	int retval = -ENOMEM;
	int id;

	mutex_lock(&minor_lock);
	if (idr_pre_get(&uio_idr, GFP_KERNEL) == 0)
		goto exit;

	retval = idr_get_new(&uio_idr, idev, &id);
	if (retval < 0) {
		if (retval == -EAGAIN)
			retval = -ENOMEM;
		goto exit;
	}
	idev->minor = id & MAX_ID_MASK;
exit:
	mutex_unlock(&minor_lock);
	return retval;
}