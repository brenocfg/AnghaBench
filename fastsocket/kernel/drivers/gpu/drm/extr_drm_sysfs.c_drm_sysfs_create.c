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
struct module {int dummy; } ;
struct class {int /*<<< orphan*/  devnode; int /*<<< orphan*/  resume; int /*<<< orphan*/  suspend; } ;

/* Variables and functions */
 struct class* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct class*) ; 
 int PTR_ERR (struct class*) ; 
 int /*<<< orphan*/  class_attr_version ; 
 struct class* class_create (struct module*,char*) ; 
 int class_create_file (struct class*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_destroy (struct class*) ; 
 int /*<<< orphan*/  drm_class_resume ; 
 int /*<<< orphan*/  drm_class_suspend ; 
 int /*<<< orphan*/  drm_devnode ; 

struct class *drm_sysfs_create(struct module *owner, char *name)
{
	struct class *class;
	int err;

	class = class_create(owner, name);
	if (IS_ERR(class)) {
		err = PTR_ERR(class);
		goto err_out;
	}

	class->suspend = drm_class_suspend;
	class->resume = drm_class_resume;

	err = class_create_file(class, &class_attr_version);
	if (err)
		goto err_out_class;

	class->devnode = drm_devnode;

	return class;

err_out_class:
	class_destroy(class);
err_out:
	return ERR_PTR(err);
}