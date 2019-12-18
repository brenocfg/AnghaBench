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
struct input_dev {struct ff_device* ff; } ;
struct file {int dummy; } ;
struct ff_device {int max_effects; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  erase_effect (struct input_dev*,int,struct file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flush_effects(struct input_dev *dev, struct file *file)
{
	struct ff_device *ff = dev->ff;
	int i;

	debug("flushing now");

	mutex_lock(&ff->mutex);

	for (i = 0; i < ff->max_effects; i++)
		erase_effect(dev, i, file);

	mutex_unlock(&ff->mutex);

	return 0;
}