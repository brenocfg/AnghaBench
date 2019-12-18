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
struct radeon_i2c_bus_rec {int dummy; } ;
struct radeon_device {scalar_t__* i2c_bus; struct drm_device* ddev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int RADEON_MAX_I2C_BUS ; 
 scalar_t__ radeon_i2c_create (struct drm_device*,struct radeon_i2c_bus_rec*,char const*) ; 

void radeon_i2c_add(struct radeon_device *rdev,
		    struct radeon_i2c_bus_rec *rec,
		    const char *name)
{
	struct drm_device *dev = rdev->ddev;
	int i;

	for (i = 0; i < RADEON_MAX_I2C_BUS; i++) {
		if (!rdev->i2c_bus[i]) {
			rdev->i2c_bus[i] = radeon_i2c_create(dev, rec, name);
			return;
		}
	}
}