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
struct nouveau_i2c {int (* identify ) (struct nouveau_i2c*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct nouveau_drm {int /*<<< orphan*/  device; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 struct nouveau_i2c* nouveau_i2c (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv04_tv_encoder_info ; 
 int stub1 (struct nouveau_i2c*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nv04_tv_identify(struct drm_device *dev, int i2c_index)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_i2c *i2c = nouveau_i2c(drm->device);

	return i2c->identify(i2c, i2c_index, "TV encoder",
			     nv04_tv_encoder_info, NULL);
}