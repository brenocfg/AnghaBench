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
struct device {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 struct device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWMON_ID_FORMAT ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int MAX_ID_MASK ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* device_create (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hwmon_class ; 
 int /*<<< orphan*/  hwmon_idr ; 
 int idr_get_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  idr_lock ; 
 scalar_t__ idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

struct device *hwmon_device_register(struct device *dev)
{
	struct device *hwdev;
	int id, err;

again:
	if (unlikely(idr_pre_get(&hwmon_idr, GFP_KERNEL) == 0))
		return ERR_PTR(-ENOMEM);

	spin_lock(&idr_lock);
	err = idr_get_new(&hwmon_idr, NULL, &id);
	spin_unlock(&idr_lock);

	if (unlikely(err == -EAGAIN))
		goto again;
	else if (unlikely(err))
		return ERR_PTR(err);

	id = id & MAX_ID_MASK;
	hwdev = device_create(hwmon_class, dev, MKDEV(0, 0), NULL,
			      HWMON_ID_FORMAT, id);

	if (IS_ERR(hwdev)) {
		spin_lock(&idr_lock);
		idr_remove(&hwmon_idr, id);
		spin_unlock(&idr_lock);
	}

	return hwdev;
}