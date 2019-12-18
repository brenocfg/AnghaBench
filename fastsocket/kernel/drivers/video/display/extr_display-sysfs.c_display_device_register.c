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
struct display_driver {int (* probe ) (struct display_device*,void*) ;} ;
struct display_device {int /*<<< orphan*/  idx; int /*<<< orphan*/  lock; struct display_driver* driver; struct device* parent; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct display_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allocated_dsp ; 
 int /*<<< orphan*/  allocated_dsp_lock ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,struct display_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_class ; 
 int idr_get_new (int /*<<< orphan*/ *,struct display_device*,int /*<<< orphan*/ *) ; 
 int idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct display_device*) ; 
 struct display_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct display_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct display_device*,void*) ; 
 scalar_t__ unlikely (int) ; 

struct display_device *display_device_register(struct display_driver *driver,
						struct device *parent, void *devdata)
{
	struct display_device *new_dev = NULL;
	int ret = -EINVAL;

	if (unlikely(!driver))
		return ERR_PTR(ret);

	mutex_lock(&allocated_dsp_lock);
	ret = idr_pre_get(&allocated_dsp, GFP_KERNEL);
	mutex_unlock(&allocated_dsp_lock);
	if (!ret)
		return ERR_PTR(ret);

	new_dev = kzalloc(sizeof(struct display_device), GFP_KERNEL);
	if (likely(new_dev) && unlikely(driver->probe(new_dev, devdata))) {
		// Reserve the index for this display
		mutex_lock(&allocated_dsp_lock);
		ret = idr_get_new(&allocated_dsp, new_dev, &new_dev->idx);
		mutex_unlock(&allocated_dsp_lock);

		if (!ret) {
			new_dev->dev = device_create(display_class, parent,
						     MKDEV(0, 0), new_dev,
						     "display%d", new_dev->idx);
			if (!IS_ERR(new_dev->dev)) {
				new_dev->parent = parent;
				new_dev->driver = driver;
				mutex_init(&new_dev->lock);
				return new_dev;
			}
			mutex_lock(&allocated_dsp_lock);
			idr_remove(&allocated_dsp, new_dev->idx);
			mutex_unlock(&allocated_dsp_lock);
			ret = -EINVAL;
		}
	}
	kfree(new_dev);
	return ERR_PTR(ret);
}