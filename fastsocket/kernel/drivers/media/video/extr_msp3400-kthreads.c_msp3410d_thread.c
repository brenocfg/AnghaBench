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
struct msp_state {scalar_t__ mode; int scan_in_progress; int v4l2_std; int watch_stereo; int nicam_on; int std; int i2s_mode; scalar_t__ has_i2s_conf; scalar_t__ has_nicam; int /*<<< orphan*/  rxsubchans; scalar_t__ radio; int /*<<< orphan*/  second; int /*<<< orphan*/  main; scalar_t__ restart; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {char* name; int retval; int /*<<< orphan*/  second; int /*<<< orphan*/  main; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSP_CARRIER (double) ; 
 scalar_t__ MSP_MODE_AM_NICAM ; 
 scalar_t__ MSP_MODE_BTSC ; 
 scalar_t__ MSP_MODE_EXTERN ; 
 scalar_t__ MSP_MODE_FM_NICAM1 ; 
 scalar_t__ MSP_MODE_FM_NICAM2 ; 
 scalar_t__ MSP_MODE_FM_RADIO ; 
 scalar_t__ MSP_MODE_FM_TERRA ; 
 int V4L2_STD_NTSC ; 
 int V4L2_STD_SECAM ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_MONO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  msp3400c_set_audmode (struct i2c_client*) ; 
 int /*<<< orphan*/  msp3400c_set_carrier (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msp3400c_set_mode (struct i2c_client*,scalar_t__) ; 
 scalar_t__ msp_amsound ; 
 scalar_t__ msp_debug ; 
 int msp_read_dem (struct i2c_client*,int) ; 
 scalar_t__ msp_sleep (struct msp_state*,int) ; 
 int /*<<< orphan*/  msp_standard_std_name (int) ; 
 TYPE_1__* msp_stdlist ; 
 int /*<<< orphan*/  msp_update_volume (struct msp_state*) ; 
 int /*<<< orphan*/  msp_write_dem (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  msp_write_dsp (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  set_freezable () ; 
 struct msp_state* to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_dbg (int,scalar_t__,struct i2c_client*,char*,...) ; 
 int /*<<< orphan*/  watch_stereo (struct i2c_client*) ; 

int msp3410d_thread(void *data)
{
	struct i2c_client *client = data;
	struct msp_state *state = to_state(i2c_get_clientdata(client));
	int val, i, std, count;

	v4l_dbg(1, msp_debug, client, "msp3410 daemon started\n");
	set_freezable();
	for (;;) {
		v4l_dbg(2, msp_debug, client, "msp3410 thread: sleep\n");
		msp_sleep(state, -1);
		v4l_dbg(2, msp_debug, client, "msp3410 thread: wakeup\n");

restart:
		v4l_dbg(2, msp_debug, client, "thread: restart scan\n");
		state->restart = 0;
		if (kthread_should_stop())
			break;

		if (state->mode == MSP_MODE_EXTERN) {
			/* no carrier scan needed, just unmute */
			v4l_dbg(1, msp_debug, client,
				"thread: no carrier scan\n");
			state->scan_in_progress = 0;
			msp_update_volume(state);
			continue;
		}

		/* mute audio */
		state->scan_in_progress = 1;
		msp_update_volume(state);

		/* start autodetect. Note: autodetect is not supported for
		   NTSC-M and radio, hence we force the standard in those
		   cases. */
		if (state->radio)
			std = 0x40;
		else
			std = (state->v4l2_std & V4L2_STD_NTSC) ? 0x20 : 1;
		state->watch_stereo = 0;
		state->nicam_on = 0;

		/* wait for tuner to settle down after a channel change */
		if (msp_sleep(state, 200))
			goto restart;

		if (msp_debug)
			v4l_dbg(2, msp_debug, client,
				"setting standard: %s (0x%04x)\n",
				msp_standard_std_name(std), std);

		if (std != 1) {
			/* programmed some specific mode */
			val = std;
		} else {
			/* triggered autodetect */
			msp_write_dem(client, 0x20, std);
			for (;;) {
				if (msp_sleep(state, 100))
					goto restart;

				/* check results */
				val = msp_read_dem(client, 0x7e);
				if (val < 0x07ff)
					break;
				v4l_dbg(2, msp_debug, client,
					"detection still in progress\n");
			}
		}
		for (i = 0; msp_stdlist[i].name != NULL; i++)
			if (msp_stdlist[i].retval == val)
				break;
		v4l_dbg(1, msp_debug, client, "current standard: %s (0x%04x)\n",
			msp_standard_std_name(val), val);
		state->main   = msp_stdlist[i].main;
		state->second = msp_stdlist[i].second;
		state->std = val;
		state->rxsubchans = V4L2_TUNER_SUB_MONO;

		if (msp_amsound && !state->radio &&
		    (state->v4l2_std & V4L2_STD_SECAM) && (val != 0x0009)) {
			/* autodetection has failed, let backup */
			v4l_dbg(1, msp_debug, client, "autodetection failed,"
				" switching to backup standard: %s (0x%04x)\n",
				msp_stdlist[8].name ?
					msp_stdlist[8].name : "unknown", val);
			state->std = val = 0x0009;
			msp_write_dem(client, 0x20, val);
		}

		/* set stereo */
		switch (val) {
		case 0x0008: /* B/G NICAM */
		case 0x000a: /* I NICAM */
		case 0x000b: /* D/K NICAM */
			if (val == 0x000a)
				state->mode = MSP_MODE_FM_NICAM2;
			else
				state->mode = MSP_MODE_FM_NICAM1;
			/* just turn on stereo */
			state->nicam_on = 1;
			state->watch_stereo = 1;
			break;
		case 0x0009:
			state->mode = MSP_MODE_AM_NICAM;
			state->nicam_on = 1;
			state->watch_stereo = 1;
			break;
		case 0x0020: /* BTSC */
			/* The pre-'G' models only have BTSC-mono */
			state->mode = MSP_MODE_BTSC;
			break;
		case 0x0040: /* FM radio */
			state->mode = MSP_MODE_FM_RADIO;
			state->rxsubchans = V4L2_TUNER_SUB_STEREO;
			/* not needed in theory if we have radio, but
			   short programming enables carrier mute */
			msp3400c_set_mode(client, MSP_MODE_FM_RADIO);
			msp3400c_set_carrier(client, MSP_CARRIER(10.7),
					    MSP_CARRIER(10.7));
			break;
		case 0x0002:
		case 0x0003:
		case 0x0004:
		case 0x0005:
			state->mode = MSP_MODE_FM_TERRA;
			state->watch_stereo = 1;
			break;
		}

		/* set various prescales */
		msp_write_dsp(client, 0x0d, 0x1900); /* scart */
		msp_write_dsp(client, 0x0e, 0x3000); /* FM */
		if (state->has_nicam)
			msp_write_dsp(client, 0x10, 0x5a00); /* nicam */

		if (state->has_i2s_conf)
			msp_write_dem(client, 0x40, state->i2s_mode);

		/* unmute */
		msp3400c_set_audmode(client);
		state->scan_in_progress = 0;
		msp_update_volume(state);

		/* monitor tv audio mode, the first time don't wait
		   so long to get a quick stereo/bilingual result */
		count = 3;
		while (state->watch_stereo) {
			if (msp_sleep(state, count ? 1000 : 5000))
				goto restart;
			if (count)
				count--;
			watch_stereo(client);
		}
	}
	v4l_dbg(1, msp_debug, client, "thread: exit\n");
	return 0;
}