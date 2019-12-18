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
typedef  int u8 ;
struct radeon_connector_atom_dig {TYPE_2__* dp_i2c_bus; } ;
struct TYPE_4__ {scalar_t__ ddc_valid; } ;
struct radeon_connector {TYPE_3__* ddc_bus; struct radeon_connector_atom_dig* con_priv; TYPE_1__ router; } ;
struct i2c_msg {int len; int* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  adapter; } ;
struct TYPE_5__ {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDC_ADDR ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int drm_edid_header_is_valid (int*) ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  radeon_router_select_ddc_port (struct radeon_connector*) ; 

bool radeon_ddc_probe(struct radeon_connector *radeon_connector, bool use_aux)
{
	u8 out = 0x0;
	u8 buf[8];
	int ret;
	struct i2c_msg msgs[] = {
		{
			.addr = DDC_ADDR,
			.flags = 0,
			.len = 1,
			.buf = &out,
		},
		{
			.addr = DDC_ADDR,
			.flags = I2C_M_RD,
			.len = 8,
			.buf = buf,
		}
	};

	/* on hw with routers, select right port */
	if (radeon_connector->router.ddc_valid)
		radeon_router_select_ddc_port(radeon_connector);

	if (use_aux) {
		struct radeon_connector_atom_dig *dig = radeon_connector->con_priv;
		ret = i2c_transfer(&dig->dp_i2c_bus->adapter, msgs, 2);
	} else {
		ret = i2c_transfer(&radeon_connector->ddc_bus->adapter, msgs, 2);
	}

	if (ret != 2)
		/* Couldn't find an accessible DDC on this connector */
		return false;
	/* Probe also for valid EDID header
	 * EDID header starts with:
	 * 0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00.
	 * Only the first 6 bytes must be valid as
	 * drm_edid_block_valid() can fix the last 2 bytes */
	if (drm_edid_header_is_valid(buf) < 6) {
		/* Couldn't find an accessible EDID on this
		 * connector */
		return false;
	}
	return true;
}