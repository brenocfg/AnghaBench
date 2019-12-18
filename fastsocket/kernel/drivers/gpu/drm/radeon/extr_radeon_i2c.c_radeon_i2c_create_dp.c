#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_11__ {TYPE_3__* algo_data; int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct TYPE_9__ {scalar_t__ address; int /*<<< orphan*/  aux_ch; } ;
struct TYPE_10__ {TYPE_3__ dp; } ;
struct radeon_i2c_bus_rec {int dummy; } ;
struct radeon_i2c_chan {TYPE_5__ adapter; TYPE_4__ algo; struct drm_device* dev; struct radeon_i2c_bus_rec rec; } ;
struct drm_device {TYPE_2__* pdev; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,char const*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_DDC ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int i2c_dp_aux_add_bus (TYPE_5__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_5__*,struct radeon_i2c_chan*) ; 
 int /*<<< orphan*/  kfree (struct radeon_i2c_chan*) ; 
 struct radeon_i2c_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_dp_i2c_aux_ch ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 

struct radeon_i2c_chan *radeon_i2c_create_dp(struct drm_device *dev,
					     struct radeon_i2c_bus_rec *rec,
					     const char *name)
{
	struct radeon_i2c_chan *i2c;
	int ret;

	i2c = kzalloc(sizeof(struct radeon_i2c_chan), GFP_KERNEL);
	if (i2c == NULL)
		return NULL;

	i2c->rec = *rec;
	i2c->adapter.owner = THIS_MODULE;
	i2c->adapter.class = I2C_CLASS_DDC;
	i2c->adapter.dev.parent = &dev->pdev->dev;
	i2c->dev = dev;
	snprintf(i2c->adapter.name, sizeof(i2c->adapter.name),
		 "Radeon aux bus %s", name);
	i2c_set_adapdata(&i2c->adapter, i2c);
	i2c->adapter.algo_data = &i2c->algo.dp;
	i2c->algo.dp.aux_ch = radeon_dp_i2c_aux_ch;
	i2c->algo.dp.address = 0;
	ret = i2c_dp_aux_add_bus(&i2c->adapter);
	if (ret) {
		DRM_INFO("Failed to register i2c %s\n", name);
		goto out_free;
	}

	return i2c;
out_free:
	kfree(i2c);
	return NULL;

}