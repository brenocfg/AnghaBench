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
struct msp_state {int main; int second; scalar_t__ mode; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ MSP_MODE_AM_NICAM ; 
 scalar_t__ MSP_MODE_FM_NICAM1 ; 
 scalar_t__ MSP_MODE_FM_NICAM2 ; 
 scalar_t__ MSP_MODE_FM_TERRA ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  msp_debug ; 
 struct msp_state* to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,int,int) ; 

__attribute__((used)) static void msp3400c_print_mode(struct i2c_client *client)
{
	struct msp_state *state = to_state(i2c_get_clientdata(client));

	if (state->main == state->second)
		v4l_dbg(1, msp_debug, client,
			"mono sound carrier: %d.%03d MHz\n",
			state->main / 910000, (state->main / 910) % 1000);
	else
		v4l_dbg(1, msp_debug, client,
			"main sound carrier: %d.%03d MHz\n",
			state->main / 910000, (state->main / 910) % 1000);
	if (state->mode == MSP_MODE_FM_NICAM1 || state->mode == MSP_MODE_FM_NICAM2)
		v4l_dbg(1, msp_debug, client,
			"NICAM/FM carrier  : %d.%03d MHz\n",
			state->second / 910000, (state->second/910) % 1000);
	if (state->mode == MSP_MODE_AM_NICAM)
		v4l_dbg(1, msp_debug, client,
			"NICAM/AM carrier  : %d.%03d MHz\n",
			state->second / 910000, (state->second / 910) % 1000);
	if (state->mode == MSP_MODE_FM_TERRA && state->main != state->second) {
		v4l_dbg(1, msp_debug, client,
			"FM-stereo carrier : %d.%03d MHz\n",
			state->second / 910000, (state->second / 910) % 1000);
	}
}