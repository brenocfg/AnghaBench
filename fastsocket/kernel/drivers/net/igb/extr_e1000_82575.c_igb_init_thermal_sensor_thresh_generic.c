#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct e1000_thermal_sensor_data {TYPE_7__* sensor; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* write_i2c_byte ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_13__ {TYPE_5__ ops; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* read ) (struct e1000_hw*,int,int,int*) ;} ;
struct TYPE_11__ {TYPE_3__ ops; } ;
struct TYPE_9__ {scalar_t__ func; } ;
struct TYPE_8__ {scalar_t__ type; struct e1000_thermal_sensor_data thermal_sensor_data; } ;
struct e1000_hw {TYPE_6__ phy; TYPE_4__ nvm; TYPE_2__ bus; TYPE_1__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_14__ {int location; int caution_thresh; int max_op_thresh; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_I2C_THERMAL_SENSOR_ADDR ; 
 int E1000_MAX_SENSORS ; 
 int /*<<< orphan*/  E1000_NOT_IMPLEMENTED ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  E1000_THHIGHTC ; 
 int /*<<< orphan*/  E1000_THLOWTC ; 
 int NVM_ETS_CFG ; 
 int NVM_ETS_DATA_HTHRESH_MASK ; 
 int NVM_ETS_DATA_INDEX_MASK ; 
 int NVM_ETS_DATA_INDEX_SHIFT ; 
 int NVM_ETS_DATA_LOC_MASK ; 
 int NVM_ETS_DATA_LOC_SHIFT ; 
 int NVM_ETS_LTHRES_DELTA_MASK ; 
 int NVM_ETS_LTHRES_DELTA_SHIFT ; 
 int NVM_ETS_NUM_SENSORS_MASK ; 
 int NVM_ETS_TYPE_EMC ; 
 int NVM_ETS_TYPE_MASK ; 
 int NVM_ETS_TYPE_SHIFT ; 
 int /*<<< orphan*/ * e1000_emc_therm_limit ; 
 scalar_t__ e1000_i350 ; 
 int /*<<< orphan*/  memset (struct e1000_thermal_sensor_data*,int /*<<< orphan*/ ,int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*,int,int,int*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*,int,int,int*) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*,int,int,int*) ; 
 int /*<<< orphan*/  stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

s32 igb_init_thermal_sensor_thresh_generic(struct e1000_hw *hw)
{
	s32 status = E1000_SUCCESS;
	u16 ets_offset;
	u16 ets_cfg;
	u16 ets_sensor;
	u8  low_thresh_delta;
	u8  num_sensors;
	u8  sensor_index;
	u8  sensor_location;
	u8  therm_limit;
	u8  i;
	struct e1000_thermal_sensor_data *data = &hw->mac.thermal_sensor_data;

	if ((hw->mac.type != e1000_i350) || (hw->bus.func != 0))
		return E1000_NOT_IMPLEMENTED;

	memset(data, 0, sizeof(struct e1000_thermal_sensor_data));

	data->sensor[0].location = 0x1;
	data->sensor[0].caution_thresh =
		(rd32(E1000_THHIGHTC) & 0xFF);
	data->sensor[0].max_op_thresh =
		(rd32(E1000_THLOWTC) & 0xFF);

	/* Return the internal sensor only if ETS is unsupported */
	hw->nvm.ops.read(hw, NVM_ETS_CFG, 1, &ets_offset);
	if ((ets_offset == 0x0000) || (ets_offset == 0xFFFF))
		return status;

	hw->nvm.ops.read(hw, ets_offset, 1, &ets_cfg);
	if (((ets_cfg & NVM_ETS_TYPE_MASK) >> NVM_ETS_TYPE_SHIFT)
	    != NVM_ETS_TYPE_EMC)
		return E1000_NOT_IMPLEMENTED;

	low_thresh_delta = ((ets_cfg & NVM_ETS_LTHRES_DELTA_MASK) >>
			    NVM_ETS_LTHRES_DELTA_SHIFT);
	num_sensors = (ets_cfg & NVM_ETS_NUM_SENSORS_MASK);

	for (i = 1; i <= num_sensors; i++) {
		hw->nvm.ops.read(hw, (ets_offset + i), 1, &ets_sensor);
		sensor_index = ((ets_sensor & NVM_ETS_DATA_INDEX_MASK) >>
				NVM_ETS_DATA_INDEX_SHIFT);
		sensor_location = ((ets_sensor & NVM_ETS_DATA_LOC_MASK) >>
				   NVM_ETS_DATA_LOC_SHIFT);
		therm_limit = ets_sensor & NVM_ETS_DATA_HTHRESH_MASK;

		hw->phy.ops.write_i2c_byte(hw,
			e1000_emc_therm_limit[sensor_index],
			E1000_I2C_THERMAL_SENSOR_ADDR,
			therm_limit);

		if ((i < E1000_MAX_SENSORS) && (sensor_location != 0)) {
			data->sensor[i].location = sensor_location;
			data->sensor[i].caution_thresh = therm_limit;
			data->sensor[i].max_op_thresh = therm_limit -
							low_thresh_delta;
		}
	}
	return status;
}