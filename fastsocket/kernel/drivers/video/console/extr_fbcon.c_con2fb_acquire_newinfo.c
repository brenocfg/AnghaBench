#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int dummy; } ;
struct fbcon_ops {int dummy; } ;
struct fb_info {TYPE_1__* fbops; struct fbcon_ops* fbcon_par; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; scalar_t__ (* fb_open ) (struct fb_info*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int* con2fb_map ; 
 struct fbcon_ops* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_blitting_type (struct vc_data*,struct fb_info*) ; 
 scalar_t__ stub1 (struct fb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int con2fb_acquire_newinfo(struct vc_data *vc, struct fb_info *info,
				  int unit, int oldidx)
{
	struct fbcon_ops *ops = NULL;
	int err = 0;

	if (!try_module_get(info->fbops->owner))
		err = -ENODEV;

	if (!err && info->fbops->fb_open &&
	    info->fbops->fb_open(info, 0))
		err = -ENODEV;

	if (!err) {
		ops = kzalloc(sizeof(struct fbcon_ops), GFP_KERNEL);
		if (!ops)
			err = -ENOMEM;
	}

	if (!err) {
		info->fbcon_par = ops;

		if (vc)
			set_blitting_type(vc, info);
	}

	if (err) {
		con2fb_map[unit] = oldidx;
		module_put(info->fbops->owner);
	}

	return err;
}