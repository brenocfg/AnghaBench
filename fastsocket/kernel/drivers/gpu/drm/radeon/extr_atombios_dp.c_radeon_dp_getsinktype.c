#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct radeon_device {int dummy; } ;
struct radeon_connector_atom_dig {TYPE_3__* dp_i2c_bus; } ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct radeon_connector {TYPE_1__ base; struct radeon_connector_atom_dig* con_priv; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_5__ {int /*<<< orphan*/  i2c_id; } ;
struct TYPE_6__ {TYPE_2__ rec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_DP_ACTION_GET_SINK_TYPE ; 
 int /*<<< orphan*/  radeon_dp_encoder_service (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 radeon_dp_getsinktype(struct radeon_connector *radeon_connector)
{
	struct radeon_connector_atom_dig *dig_connector = radeon_connector->con_priv;
	struct drm_device *dev = radeon_connector->base.dev;
	struct radeon_device *rdev = dev->dev_private;

	return radeon_dp_encoder_service(rdev, ATOM_DP_ACTION_GET_SINK_TYPE, 0,
					 dig_connector->dp_i2c_bus->rec.i2c_id, 0);
}