#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lcd_ops {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  release; struct device* parent; int /*<<< orphan*/  class; } ;
struct lcd_device {struct lcd_ops* ops; TYPE_1__ dev; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  ops_lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct lcd_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char const*) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct lcd_device*) ; 
 struct lcd_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_class ; 
 int /*<<< orphan*/  lcd_device_release ; 
 int lcd_register_fb (struct lcd_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 

struct lcd_device *lcd_device_register(const char *name, struct device *parent,
		void *devdata, struct lcd_ops *ops)
{
	struct lcd_device *new_ld;
	int rc;

	pr_debug("lcd_device_register: name=%s\n", name);

	new_ld = kzalloc(sizeof(struct lcd_device), GFP_KERNEL);
	if (!new_ld)
		return ERR_PTR(-ENOMEM);

	mutex_init(&new_ld->ops_lock);
	mutex_init(&new_ld->update_lock);

	new_ld->dev.class = lcd_class;
	new_ld->dev.parent = parent;
	new_ld->dev.release = lcd_device_release;
	dev_set_name(&new_ld->dev, name);
	dev_set_drvdata(&new_ld->dev, devdata);

	rc = device_register(&new_ld->dev);
	if (rc) {
		kfree(new_ld);
		return ERR_PTR(rc);
	}

	rc = lcd_register_fb(new_ld);
	if (rc) {
		device_unregister(&new_ld->dev);
		return ERR_PTR(rc);
	}

	new_ld->ops = ops;

	return new_ld;
}