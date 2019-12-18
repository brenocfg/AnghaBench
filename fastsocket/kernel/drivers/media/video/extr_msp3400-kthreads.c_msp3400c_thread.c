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
struct msp_state {scalar_t__ mode; int scan_in_progress; int watch_stereo; int nicam_on; int v4l2_std; int /*<<< orphan*/  main; int /*<<< orphan*/  second; int /*<<< orphan*/  has_nicam; scalar_t__ radio; scalar_t__ restart; } ;
struct msp3400c_carrier_detect {int /*<<< orphan*/  cdo; int /*<<< orphan*/  name; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct msp3400c_carrier_detect*) ; 
 int /*<<< orphan*/  MSP_CARRIER (double) ; 
 int /*<<< orphan*/  MSP_MODE_AM_DETECT ; 
 int /*<<< orphan*/  MSP_MODE_AM_NICAM ; 
 scalar_t__ MSP_MODE_EXTERN ; 
 int /*<<< orphan*/  MSP_MODE_FM_NICAM1 ; 
 int /*<<< orphan*/  MSP_MODE_FM_NICAM2 ; 
 int /*<<< orphan*/  MSP_MODE_FM_TERRA ; 
 int V4L2_STD_SECAM ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ kthread_should_stop () ; 
 struct msp3400c_carrier_detect* msp3400c_carrier_detect_55 ; 
 struct msp3400c_carrier_detect* msp3400c_carrier_detect_65 ; 
 struct msp3400c_carrier_detect* msp3400c_carrier_detect_main ; 
 int /*<<< orphan*/  msp3400c_print_mode (struct i2c_client*) ; 
 int /*<<< orphan*/  msp3400c_set_audmode (struct i2c_client*) ; 
 int /*<<< orphan*/  msp3400c_set_carrier (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msp3400c_set_mode (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ msp_amsound ; 
 scalar_t__ msp_debug ; 
 int msp_read_dsp (struct i2c_client*,int) ; 
 scalar_t__ msp_sleep (struct msp_state*,int) ; 
 int /*<<< orphan*/  msp_update_volume (struct msp_state*) ; 
 int /*<<< orphan*/  set_freezable () ; 
 struct msp_state* to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_dbg (int,scalar_t__,struct i2c_client*,char*,...) ; 
 int /*<<< orphan*/  watch_stereo (struct i2c_client*) ; 

int msp3400c_thread(void *data)
{
	struct i2c_client *client = data;
	struct msp_state *state = to_state(i2c_get_clientdata(client));
	struct msp3400c_carrier_detect *cd;
	int count, max1, max2, val1, val2, val, i;

	v4l_dbg(1, msp_debug, client, "msp3400 daemon started\n");
	set_freezable();
	for (;;) {
		v4l_dbg(2, msp_debug, client, "msp3400 thread: sleep\n");
		msp_sleep(state, -1);
		v4l_dbg(2, msp_debug, client, "msp3400 thread: wakeup\n");

restart:
		v4l_dbg(2, msp_debug, client, "thread: restart scan\n");
		state->restart = 0;
		if (kthread_should_stop())
			break;

		if (state->radio || MSP_MODE_EXTERN == state->mode) {
			/* no carrier scan, just unmute */
			v4l_dbg(1, msp_debug, client,
				"thread: no carrier scan\n");
			state->scan_in_progress = 0;
			msp_update_volume(state);
			continue;
		}

		/* mute audio */
		state->scan_in_progress = 1;
		msp_update_volume(state);

		msp3400c_set_mode(client, MSP_MODE_AM_DETECT);
		val1 = val2 = 0;
		max1 = max2 = -1;
		state->watch_stereo = 0;
		state->nicam_on = 0;

		/* wait for tuner to settle down after a channel change */
		if (msp_sleep(state, 200))
			goto restart;

		/* carrier detect pass #1 -- main carrier */
		cd = msp3400c_carrier_detect_main;
		count = ARRAY_SIZE(msp3400c_carrier_detect_main);

		if (msp_amsound && (state->v4l2_std & V4L2_STD_SECAM)) {
			/* autodetect doesn't work well with AM ... */
			max1 = 3;
			count = 0;
			v4l_dbg(1, msp_debug, client, "AM sound override\n");
		}

		for (i = 0; i < count; i++) {
			msp3400c_set_carrier(client, cd[i].cdo, cd[i].cdo);
			if (msp_sleep(state, 100))
				goto restart;
			val = msp_read_dsp(client, 0x1b);
			if (val > 32767)
				val -= 65536;
			if (val1 < val)
				val1 = val, max1 = i;
			v4l_dbg(1, msp_debug, client,
				"carrier1 val: %5d / %s\n", val, cd[i].name);
		}

		/* carrier detect pass #2 -- second (stereo) carrier */
		switch (max1) {
		case 1: /* 5.5 */
			cd = msp3400c_carrier_detect_55;
			count = ARRAY_SIZE(msp3400c_carrier_detect_55);
			break;
		case 3: /* 6.5 */
			cd = msp3400c_carrier_detect_65;
			count = ARRAY_SIZE(msp3400c_carrier_detect_65);
			break;
		case 0: /* 4.5 */
		case 2: /* 6.0 */
		default:
			cd = NULL;
			count = 0;
			break;
		}

		if (msp_amsound && (state->v4l2_std & V4L2_STD_SECAM)) {
			/* autodetect doesn't work well with AM ... */
			cd = NULL;
			count = 0;
			max2 = 0;
		}
		for (i = 0; i < count; i++) {
			msp3400c_set_carrier(client, cd[i].cdo, cd[i].cdo);
			if (msp_sleep(state, 100))
				goto restart;
			val = msp_read_dsp(client, 0x1b);
			if (val > 32767)
				val -= 65536;
			if (val2 < val)
				val2 = val, max2 = i;
			v4l_dbg(1, msp_debug, client,
				"carrier2 val: %5d / %s\n", val, cd[i].name);
		}

		/* program the msp3400 according to the results */
		state->main = msp3400c_carrier_detect_main[max1].cdo;
		switch (max1) {
		case 1: /* 5.5 */
			if (max2 == 0) {
				/* B/G FM-stereo */
				state->second = msp3400c_carrier_detect_55[max2].cdo;
				msp3400c_set_mode(client, MSP_MODE_FM_TERRA);
				state->watch_stereo = 1;
			} else if (max2 == 1 && state->has_nicam) {
				/* B/G NICAM */
				state->second = msp3400c_carrier_detect_55[max2].cdo;
				msp3400c_set_mode(client, MSP_MODE_FM_NICAM1);
				state->nicam_on = 1;
				state->watch_stereo = 1;
			} else {
				goto no_second;
			}
			break;
		case 2: /* 6.0 */
			/* PAL I NICAM */
			state->second = MSP_CARRIER(6.552);
			msp3400c_set_mode(client, MSP_MODE_FM_NICAM2);
			state->nicam_on = 1;
			state->watch_stereo = 1;
			break;
		case 3: /* 6.5 */
			if (max2 == 1 || max2 == 2) {
				/* D/K FM-stereo */
				state->second = msp3400c_carrier_detect_65[max2].cdo;
				msp3400c_set_mode(client, MSP_MODE_FM_TERRA);
				state->watch_stereo = 1;
			} else if (max2 == 0 && (state->v4l2_std & V4L2_STD_SECAM)) {
				/* L NICAM or AM-mono */
				state->second = msp3400c_carrier_detect_65[max2].cdo;
				msp3400c_set_mode(client, MSP_MODE_AM_NICAM);
				state->watch_stereo = 1;
			} else if (max2 == 0 && state->has_nicam) {
				/* D/K NICAM */
				state->second = msp3400c_carrier_detect_65[max2].cdo;
				msp3400c_set_mode(client, MSP_MODE_FM_NICAM1);
				state->nicam_on = 1;
				state->watch_stereo = 1;
			} else {
				goto no_second;
			}
			break;
		case 0: /* 4.5 */
		default:
no_second:
			state->second = msp3400c_carrier_detect_main[max1].cdo;
			msp3400c_set_mode(client, MSP_MODE_FM_TERRA);
			break;
		}
		msp3400c_set_carrier(client, state->second, state->main);

		/* unmute */
		state->scan_in_progress = 0;
		msp3400c_set_audmode(client);
		msp_update_volume(state);

		if (msp_debug)
			msp3400c_print_mode(client);

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