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
typedef  int u32 ;
struct v4l2_subdev {int grp_id; } ;
struct i2c_adapter {int dummy; } ;
struct ivtv {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  pvr150_workaround; TYPE_1__* card_i2c; struct i2c_adapter i2c_adap; } ;
struct cx25840_platform_data {int /*<<< orphan*/  pvr150_workaround; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tv; int /*<<< orphan*/ * demod; int /*<<< orphan*/ * radio; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * I2C_ADDRS (int /*<<< orphan*/ ) ; 
 int IVTV_HW_CX25840 ; 
 int IVTV_HW_IR_ANY ; 
 int IVTV_HW_TUNER ; 
 int IVTV_HW_UPD64031A ; 
 int IVTV_HW_UPD6408X ; 
 int /*<<< orphan*/ * hw_addrs ; 
 char** hw_devicenames ; 
 int ivtv_i2c_new_ir (struct ivtv*,int,char const*,int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* v4l2_i2c_new_subdev (int /*<<< orphan*/ *,struct i2c_adapter*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct v4l2_subdev* v4l2_i2c_new_subdev_cfg (int /*<<< orphan*/ *,struct i2c_adapter*,char const*,int /*<<< orphan*/ ,struct cx25840_platform_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ivtv_i2c_register(struct ivtv *itv, unsigned idx)
{
	struct v4l2_subdev *sd;
	struct i2c_adapter *adap = &itv->i2c_adap;
	const char *type = hw_devicenames[idx];
	u32 hw = 1 << idx;

	if (idx >= ARRAY_SIZE(hw_addrs))
		return -1;
	if (hw == IVTV_HW_TUNER) {
		/* special tuner handling */
		sd = v4l2_i2c_new_subdev(&itv->v4l2_dev, adap, type, 0,
				itv->card_i2c->radio);
		if (sd)
			sd->grp_id = 1 << idx;
		sd = v4l2_i2c_new_subdev(&itv->v4l2_dev, adap, type, 0,
				itv->card_i2c->demod);
		if (sd)
			sd->grp_id = 1 << idx;
		sd = v4l2_i2c_new_subdev(&itv->v4l2_dev, adap, type, 0,
				itv->card_i2c->tv);
		if (sd)
			sd->grp_id = 1 << idx;
		return sd ? 0 : -1;
	}

	if (hw & IVTV_HW_IR_ANY)
		return ivtv_i2c_new_ir(itv, hw, type, hw_addrs[idx]);

	/* Is it not an I2C device or one we do not wish to register? */
	if (!hw_addrs[idx])
		return -1;

	/* It's an I2C device other than an analog tuner or IR chip */
	if (hw == IVTV_HW_UPD64031A || hw == IVTV_HW_UPD6408X) {
		sd = v4l2_i2c_new_subdev(&itv->v4l2_dev,
				adap, type, 0, I2C_ADDRS(hw_addrs[idx]));
	} else if (hw == IVTV_HW_CX25840) {
		struct cx25840_platform_data pdata;

		pdata.pvr150_workaround = itv->pvr150_workaround;
		sd = v4l2_i2c_new_subdev_cfg(&itv->v4l2_dev,
				adap, type, 0, &pdata, hw_addrs[idx], NULL);
	} else {
		sd = v4l2_i2c_new_subdev(&itv->v4l2_dev,
				adap, type, hw_addrs[idx], NULL);
	}
	if (sd)
		sd->grp_id = 1 << idx;
	return sd ? 0 : -1;
}