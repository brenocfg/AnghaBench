#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct output_properties {int dummy; } ;
struct TYPE_4__ {struct device* parent; int /*<<< orphan*/ * class; } ;
struct output_device {TYPE_1__ dev; struct output_properties* props; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct output_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char const*) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct output_device*) ; 
 struct output_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_output_class ; 

struct output_device *video_output_register(const char *name,
	struct device *dev,
	void *devdata,
	struct output_properties *op)
{
	struct output_device *new_dev;
	int ret_code = 0;

	new_dev = kzalloc(sizeof(struct output_device),GFP_KERNEL);
	if (!new_dev) {
		ret_code = -ENOMEM;
		goto error_return;
	}
	new_dev->props = op;
	new_dev->dev.class = &video_output_class;
	new_dev->dev.parent = dev;
	dev_set_name(&new_dev->dev, name);
	dev_set_drvdata(&new_dev->dev, devdata);
	ret_code = device_register(&new_dev->dev);
	if (ret_code) {
		kfree(new_dev);
		goto error_return;
	}
	return new_dev;

error_return:
	return ERR_PTR(ret_code);
}