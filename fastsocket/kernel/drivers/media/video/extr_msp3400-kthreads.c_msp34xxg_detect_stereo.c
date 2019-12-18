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
struct msp_state {int rxsubchans; scalar_t__ mode; int std; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ MSP_MODE_EXTERN ; 
 int V4L2_TUNER_SUB_LANG1 ; 
 int V4L2_TUNER_SUB_LANG2 ; 
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_SAP ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  msp_debug ; 
 int msp_read_dem (struct i2c_client*,int) ; 
 struct msp_state* to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,int,int,int,int) ; 

__attribute__((used)) static int msp34xxg_detect_stereo(struct i2c_client *client)
{
	struct msp_state *state = to_state(i2c_get_clientdata(client));
	int status = msp_read_dem(client, 0x0200);
	int is_bilingual = status & 0x100;
	int is_stereo = status & 0x40;
	int oldrx = state->rxsubchans;

	if (state->mode == MSP_MODE_EXTERN)
		return 0;

	state->rxsubchans = 0;
	if (is_stereo)
		state->rxsubchans = V4L2_TUNER_SUB_STEREO;
	else
		state->rxsubchans = V4L2_TUNER_SUB_MONO;
	if (is_bilingual) {
		if (state->std == 0x20)
			state->rxsubchans |= V4L2_TUNER_SUB_SAP;
		else
			state->rxsubchans =
				V4L2_TUNER_SUB_LANG1 | V4L2_TUNER_SUB_LANG2;
	}
	v4l_dbg(1, msp_debug, client,
		"status=0x%x, stereo=%d, bilingual=%d -> rxsubchans=%d\n",
		status, is_stereo, is_bilingual, state->rxsubchans);
	return (oldrx != state->rxsubchans);
}