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
typedef  struct tuner_setup* v4l2_std_id ;
struct tuner_setup {int /*<<< orphan*/  frequency; int /*<<< orphan*/  type; scalar_t__ tuner; int /*<<< orphan*/  addr; int /*<<< orphan*/  mode_mask; } ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct mxb {size_t cur_input; int cur_mute; int /*<<< orphan*/  i2c_adapter; int /*<<< orphan*/  cur_mode; struct tuner_setup cur_freq; } ;
struct i2c_msg {int addr; int len; int /*<<< orphan*/ * buf; scalar_t__ flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  hps_sync; int /*<<< orphan*/  hps_source; } ;
struct TYPE_4__ {int length; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_UNSET ; 
 int /*<<< orphan*/  DD1_INIT ; 
 int /*<<< orphan*/  DD1_STREAM_B ; 
 int /*<<< orphan*/  DEB_D (char*) ; 
 int /*<<< orphan*/  INFO (char*) ; 
 int MASK_09 ; 
 int MASK_10 ; 
 int MASK_25 ; 
 int MASK_26 ; 
 int /*<<< orphan*/  MC2 ; 
 int SAA7111_FMT_CCIR ; 
 int SAA7111_VBI_BYPASS ; 
 int /*<<< orphan*/  SAA7115_COMPOSITE0 ; 
 int /*<<< orphan*/  SAA7146_USE_I2C_IRQ ; 
 int /*<<< orphan*/  TUNER_PHILIPS_PAL ; 
 int /*<<< orphan*/  T_ANALOG_TV ; 
 struct tuner_setup* V4L2_STD_PAL_BG ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  core ; 
 TYPE_3__ extension ; 
 int /*<<< orphan*/  freq ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 TYPE_2__* input_port_selection ; 
 TYPE_1__* mxb_saa7740_init ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  s_routing ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  s_type_addr ; 
 int /*<<< orphan*/  saa7111a_call (struct mxb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tuner_setup*,...) ; 
 int /*<<< orphan*/  saa7146_set_hps_source_and_sync (struct saa7146_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tea6415c_call (struct mxb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tea6420_route_cd (struct mxb*,int) ; 
 int /*<<< orphan*/  tea6420_route_line (struct mxb*,int) ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  tuner_call (struct mxb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tuner_setup*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int mxb_init_done(struct saa7146_dev* dev)
{
	struct mxb* mxb = (struct mxb*)dev->ext_priv;
	struct i2c_msg msg;
	struct tuner_setup tun_setup;
	v4l2_std_id std = V4L2_STD_PAL_BG;

	int i = 0, err = 0;

	/* select video mode in saa7111a */
	saa7111a_call(mxb, core, s_std, std);

	/* select tuner-output on saa7111a */
	i = 0;
	saa7111a_call(mxb, video, s_routing, SAA7115_COMPOSITE0,
		SAA7111_FMT_CCIR | SAA7111_VBI_BYPASS, 0);

	/* select a tuner type */
	tun_setup.mode_mask = T_ANALOG_TV;
	tun_setup.addr = ADDR_UNSET;
	tun_setup.type = TUNER_PHILIPS_PAL;
	tuner_call(mxb, tuner, s_type_addr, &tun_setup);
	/* tune in some frequency on tuner */
	mxb->cur_freq.tuner = 0;
	mxb->cur_freq.type = V4L2_TUNER_ANALOG_TV;
	mxb->cur_freq.frequency = freq;
	tuner_call(mxb, tuner, s_frequency, &mxb->cur_freq);

	/* set a default video standard */
	tuner_call(mxb, core, s_std, std);

	/* mute audio on tea6420s */
	tea6420_route_line(mxb, 6);
	tea6420_route_cd(mxb, 6);

	/* switch to tuner-channel on tea6415c */
	tea6415c_call(mxb, video, s_routing, 3, 17, 0);

	/* select tuner-output on multicable on tea6415c */
	tea6415c_call(mxb, video, s_routing, 3, 13, 0);

	/* the rest for mxb */
	mxb->cur_input = 0;
	mxb->cur_mute = 1;

	mxb->cur_mode = V4L2_TUNER_MODE_STEREO;

	/* check if the saa7740 (aka 'sound arena module') is present
	   on the mxb. if so, we must initialize it. due to lack of
	   informations about the saa7740, the values were reverse
	   engineered. */
	msg.addr = 0x1b;
	msg.flags = 0;
	msg.len = mxb_saa7740_init[0].length;
	msg.buf = &mxb_saa7740_init[0].data[0];

	err = i2c_transfer(&mxb->i2c_adapter, &msg, 1);
	if (err == 1) {
		/* the sound arena module is a pos, that's probably the reason
		   philips refuses to hand out a datasheet for the saa7740...
		   it seems to screw up the i2c bus, so we disable fast irq
		   based i2c transactions here and rely on the slow and safe
		   polling method ... */
		extension.flags &= ~SAA7146_USE_I2C_IRQ;
		for (i = 1; ; i++) {
			if (-1 == mxb_saa7740_init[i].length)
				break;

			msg.len = mxb_saa7740_init[i].length;
			msg.buf = &mxb_saa7740_init[i].data[0];
			err = i2c_transfer(&mxb->i2c_adapter, &msg, 1);
			if (err != 1) {
				DEB_D(("failed to initialize 'sound arena module'.\n"));
				goto err;
			}
		}
		INFO(("'sound arena module' detected.\n"));
	}
err:
	/* the rest for saa7146: you should definitely set some basic values
	   for the input-port handling of the saa7146. */

	/* ext->saa has been filled by the core driver */

	/* some stuff is done via variables */
	saa7146_set_hps_source_and_sync(dev, input_port_selection[mxb->cur_input].hps_source,
			input_port_selection[mxb->cur_input].hps_sync);

	/* some stuff is done via direct write to the registers */

	/* this is ugly, but because of the fact that this is completely
	   hardware dependend, it should be done directly... */
	saa7146_write(dev, DD1_STREAM_B,	0x00000000);
	saa7146_write(dev, DD1_INIT,		0x02000200);
	saa7146_write(dev, MC2, (MASK_09 | MASK_25 | MASK_10 | MASK_26));

	return 0;
}