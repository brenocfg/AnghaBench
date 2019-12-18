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
struct msp_state {scalar_t__ mode; int std; int acb; int watch_stereo; scalar_t__ force_btsc; scalar_t__ radio; scalar_t__ scan_in_progress; scalar_t__ restart; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ MSP_MODE_EXTERN ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  msp34xxg_reset (struct i2c_client*) ; 
 int /*<<< orphan*/  msp_debug ; 
 int msp_read_dem (struct i2c_client*,int) ; 
 scalar_t__ msp_sleep (struct msp_state*,int) ; 
 int msp_standard ; 
 int /*<<< orphan*/  msp_standard_std_name (int) ; 
 int /*<<< orphan*/  msp_update_volume (struct msp_state*) ; 
 int /*<<< orphan*/  msp_write_dem (struct i2c_client*,int,int) ; 
 scalar_t__ msp_write_dsp (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  set_freezable () ; 
 struct msp_state* to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,...) ; 
 int /*<<< orphan*/  watch_stereo (struct i2c_client*) ; 

int msp34xxg_thread(void *data)
{
	struct i2c_client *client = data;
	struct msp_state *state = to_state(i2c_get_clientdata(client));
	int val, i;

	v4l_dbg(1, msp_debug, client, "msp34xxg daemon started\n");
	set_freezable();
	for (;;) {
		v4l_dbg(2, msp_debug, client, "msp34xxg thread: sleep\n");
		msp_sleep(state, -1);
		v4l_dbg(2, msp_debug, client, "msp34xxg thread: wakeup\n");

restart:
		v4l_dbg(1, msp_debug, client, "thread: restart scan\n");
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

		/* setup the chip*/
		msp34xxg_reset(client);
		state->std = state->radio ? 0x40 :
			(state->force_btsc && msp_standard == 1) ? 32 : msp_standard;
		msp_write_dem(client, 0x20, state->std);
		/* start autodetect */
		if (state->std != 1)
			goto unmute;

		/* watch autodetect */
		v4l_dbg(1, msp_debug, client,
			"started autodetect, waiting for result\n");
		for (i = 0; i < 10; i++) {
			if (msp_sleep(state, 100))
				goto restart;

			/* check results */
			val = msp_read_dem(client, 0x7e);
			if (val < 0x07ff) {
				state->std = val;
				break;
			}
			v4l_dbg(2, msp_debug, client,
				"detection still in progress\n");
		}
		if (state->std == 1) {
			v4l_dbg(1, msp_debug, client,
				"detection still in progress after 10 tries. giving up.\n");
			continue;
		}

unmute:
		v4l_dbg(1, msp_debug, client,
			"detected standard: %s (0x%04x)\n",
			msp_standard_std_name(state->std), state->std);

		if (state->std == 9) {
			/* AM NICAM mode */
			msp_write_dsp(client, 0x0e, 0x7c00);
		}

		/* unmute: dispatch sound to scart output, set scart volume */
		msp_update_volume(state);

		/* restore ACB */
		if (msp_write_dsp(client, 0x13, state->acb))
			return -1;

		/* the periodic stereo/SAP check is only relevant for
		   the 0x20 standard (BTSC) */
		if (state->std != 0x20)
			continue;

		state->watch_stereo = 1;

		/* monitor tv audio mode, the first time don't wait
		   in order to get a quick stereo/SAP update */
		watch_stereo(client);
		while (state->watch_stereo) {
			watch_stereo(client);
			if (msp_sleep(state, 5000))
				goto restart;
		}
	}
	v4l_dbg(1, msp_debug, client, "thread: exit\n");
	return 0;
}