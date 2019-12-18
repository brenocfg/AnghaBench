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
typedef  int v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct saa7127_state {scalar_t__ ident; int std; int /*<<< orphan*/  reg_61; } ;
struct i2c_reg_value {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7127_50HZ_PAL_DAC_CONTROL ; 
 int /*<<< orphan*/  SAA7127_50HZ_SECAM_DAC_CONTROL ; 
 int /*<<< orphan*/  SAA7127_60HZ_DAC_CONTROL ; 
 scalar_t__ V4L2_IDENT_SAA7129 ; 
 int V4L2_STD_525_60 ; 
 int V4L2_STD_625_50 ; 
 int V4L2_STD_SECAM ; 
 int /*<<< orphan*/  debug ; 
 struct i2c_reg_value* saa7127_init_config_50hz_pal ; 
 struct i2c_reg_value* saa7127_init_config_50hz_secam ; 
 struct i2c_reg_value* saa7127_init_config_60hz ; 
 int /*<<< orphan*/  saa7127_write_inittab (struct v4l2_subdev*,struct i2c_reg_value const*) ; 
 struct saa7127_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int saa7127_set_std(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct saa7127_state *state = to_state(sd);
	const struct i2c_reg_value *inittab;

	if (std & V4L2_STD_525_60) {
		v4l2_dbg(1, debug, sd, "Selecting 60 Hz video Standard\n");
		inittab = saa7127_init_config_60hz;
		state->reg_61 = SAA7127_60HZ_DAC_CONTROL;

	} else if (state->ident == V4L2_IDENT_SAA7129 &&
		   (std & V4L2_STD_SECAM) &&
		   !(std & (V4L2_STD_625_50 & ~V4L2_STD_SECAM))) {

		/* If and only if SECAM, with a SAA712[89] */
		v4l2_dbg(1, debug, sd,
			 "Selecting 50 Hz SECAM video Standard\n");
		inittab = saa7127_init_config_50hz_secam;
		state->reg_61 = SAA7127_50HZ_SECAM_DAC_CONTROL;

	} else {
		v4l2_dbg(1, debug, sd, "Selecting 50 Hz PAL video Standard\n");
		inittab = saa7127_init_config_50hz_pal;
		state->reg_61 = SAA7127_50HZ_PAL_DAC_CONTROL;
	}

	/* Write Table */
	saa7127_write_inittab(sd, inittab);
	state->std = std;
	return 0;
}