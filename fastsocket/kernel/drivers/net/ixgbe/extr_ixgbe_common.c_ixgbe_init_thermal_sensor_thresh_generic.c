#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  size_t u16 ;
struct ixgbe_thermal_sensor_data {TYPE_6__* sensor; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* write_i2c_byte ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ;} ;
struct TYPE_11__ {TYPE_4__ ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* read ) (struct ixgbe_hw*,size_t,size_t*) ;} ;
struct TYPE_9__ {TYPE_2__ ops; } ;
struct TYPE_7__ {struct ixgbe_thermal_sensor_data thermal_sensor_data; } ;
struct ixgbe_hw {TYPE_5__ phy; TYPE_3__ eeprom; TYPE_1__ mac; } ;
typedef  scalar_t__ s32 ;
struct TYPE_12__ {size_t location; size_t caution_thresh; size_t max_op_thresh; } ;

/* Variables and functions */
 size_t IXGBE_ETS_DATA_HTHRESH_MASK ; 
 size_t IXGBE_ETS_DATA_INDEX_MASK ; 
 size_t IXGBE_ETS_DATA_INDEX_SHIFT ; 
 size_t IXGBE_ETS_DATA_LOC_MASK ; 
 size_t IXGBE_ETS_DATA_LOC_SHIFT ; 
 size_t IXGBE_ETS_LTHRES_DELTA_MASK ; 
 size_t IXGBE_ETS_LTHRES_DELTA_SHIFT ; 
 size_t IXGBE_ETS_NUM_SENSORS_MASK ; 
 int /*<<< orphan*/  IXGBE_I2C_THERMAL_SENSOR_ADDR ; 
 size_t IXGBE_MAX_SENSORS ; 
 scalar_t__ IXGBE_NOT_IMPLEMENTED ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_STATUS ; 
 int IXGBE_STATUS_LAN_ID_1 ; 
 int /*<<< orphan*/ * ixgbe_emc_therm_limit ; 
 scalar_t__ ixgbe_get_ets_data (struct ixgbe_hw*,size_t*,size_t*) ; 
 int /*<<< orphan*/  memset (struct ixgbe_thermal_sensor_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,size_t,size_t*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

s32 ixgbe_init_thermal_sensor_thresh_generic(struct ixgbe_hw *hw)
{
	s32 status = 0;
	u16 ets_offset;
	u16 ets_cfg;
	u16 ets_sensor;
	u8  low_thresh_delta;
	u8  num_sensors;
	u8  therm_limit;
	u8  i;
	struct ixgbe_thermal_sensor_data *data = &hw->mac.thermal_sensor_data;

	memset(data, 0, sizeof(struct ixgbe_thermal_sensor_data));

	/* Only support thermal sensors attached to physical port 0 */
	if ((IXGBE_READ_REG(hw, IXGBE_STATUS) & IXGBE_STATUS_LAN_ID_1)) {
		status = IXGBE_NOT_IMPLEMENTED;
		goto out;
	}

	status = ixgbe_get_ets_data(hw, &ets_cfg, &ets_offset);
	if (status)
		goto out;

	low_thresh_delta = ((ets_cfg & IXGBE_ETS_LTHRES_DELTA_MASK) >>
			     IXGBE_ETS_LTHRES_DELTA_SHIFT);
	num_sensors = (ets_cfg & IXGBE_ETS_NUM_SENSORS_MASK);
	if (num_sensors > IXGBE_MAX_SENSORS)
		num_sensors = IXGBE_MAX_SENSORS;

	for (i = 0; i < num_sensors; i++) {
		u8  sensor_index;
		u8  sensor_location;

		hw->eeprom.ops.read(hw, (ets_offset + 1 + i), &ets_sensor);
		sensor_index = ((ets_sensor & IXGBE_ETS_DATA_INDEX_MASK) >>
				IXGBE_ETS_DATA_INDEX_SHIFT);
		sensor_location = ((ets_sensor & IXGBE_ETS_DATA_LOC_MASK) >>
				   IXGBE_ETS_DATA_LOC_SHIFT);
		therm_limit = ets_sensor & IXGBE_ETS_DATA_HTHRESH_MASK;

		hw->phy.ops.write_i2c_byte(hw,
			ixgbe_emc_therm_limit[sensor_index],
			IXGBE_I2C_THERMAL_SENSOR_ADDR, therm_limit);

		if (sensor_location == 0)
			continue;

		data->sensor[i].location = sensor_location;
		data->sensor[i].caution_thresh = therm_limit;
		data->sensor[i].max_op_thresh = therm_limit - low_thresh_delta;
	}
out:
	return status;
}