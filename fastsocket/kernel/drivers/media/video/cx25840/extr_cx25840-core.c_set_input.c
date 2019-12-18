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
typedef  int u8 ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int vid_input; int aud_input; } ;
typedef  enum cx25840_video_input { ____Placeholder_cx25840_video_input } cx25840_video_input ;
typedef  enum cx25840_audio_input { ____Placeholder_cx25840_audio_input } cx25840_audio_input ;

/* Variables and functions */
#define  CX25840_AUDIO4 133 
#define  CX25840_AUDIO5 132 
#define  CX25840_AUDIO6 131 
#define  CX25840_AUDIO7 130 
#define  CX25840_AUDIO8 129 
#define  CX25840_AUDIO_SERIAL 128 
 int CX25840_COMPONENT_ON ; 
 int CX25840_COMPOSITE1 ; 
 int CX25840_COMPOSITE8 ; 
 int CX25840_SVIDEO_CHROMA4 ; 
 int CX25840_SVIDEO_CHROMA7 ; 
 int CX25840_SVIDEO_CHROMA8 ; 
 int CX25840_SVIDEO_LUMA1 ; 
 int CX25840_SVIDEO_LUMA8 ; 
 int CX25840_SVIDEO_ON ; 
 int CX25840_VIN1_CH1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  cx25840_and_or (struct i2c_client*,int,int,int) ; 
 int /*<<< orphan*/  cx25840_audio_set_path (struct i2c_client*) ; 
 int /*<<< orphan*/  cx25840_debug ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_change (struct i2c_client*) ; 
 scalar_t__ is_cx231xx (struct cx25840_state*) ; 
 scalar_t__ is_cx2388x (struct cx25840_state*) ; 
 struct cx25840_state* to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,int,...) ; 
 int /*<<< orphan*/  v4l_err (struct i2c_client*,char*,int) ; 

__attribute__((used)) static int set_input(struct i2c_client *client, enum cx25840_video_input vid_input,
						enum cx25840_audio_input aud_input)
{
	struct cx25840_state *state = to_state(i2c_get_clientdata(client));
	u8 is_composite = (vid_input >= CX25840_COMPOSITE1 &&
			   vid_input <= CX25840_COMPOSITE8);
	u8 is_component = (vid_input & CX25840_COMPONENT_ON) ==
			CX25840_COMPONENT_ON;
	int luma = vid_input & 0xf0;
	int chroma = vid_input & 0xf00;
	u8 reg;

	v4l_dbg(1, cx25840_debug, client,
		"decoder set video input %d, audio input %d\n",
		vid_input, aud_input);

	if (vid_input >= CX25840_VIN1_CH1) {
		v4l_dbg(1, cx25840_debug, client, "vid_input 0x%x\n",
			vid_input);
		reg = vid_input & 0xff;
		is_composite = !is_component &&
			((vid_input & CX25840_SVIDEO_ON) != CX25840_SVIDEO_ON);

		v4l_dbg(1, cx25840_debug, client, "mux cfg 0x%x comp=%d\n",
			reg, is_composite);
	} else if (is_composite) {
		reg = 0xf0 + (vid_input - CX25840_COMPOSITE1);
	} else {
		if ((vid_input & ~0xff0) ||
		    luma < CX25840_SVIDEO_LUMA1 || luma > CX25840_SVIDEO_LUMA8 ||
		    chroma < CX25840_SVIDEO_CHROMA4 || chroma > CX25840_SVIDEO_CHROMA8) {
			v4l_err(client, "0x%04x is not a valid video input!\n",
				vid_input);
			return -EINVAL;
		}
		reg = 0xf0 + ((luma - CX25840_SVIDEO_LUMA1) >> 4);
		if (chroma >= CX25840_SVIDEO_CHROMA7) {
			reg &= 0x3f;
			reg |= (chroma - CX25840_SVIDEO_CHROMA7) >> 2;
		} else {
			reg &= 0xcf;
			reg |= (chroma - CX25840_SVIDEO_CHROMA4) >> 4;
		}
	}

	/* The caller has previously prepared the correct routing
	 * configuration in reg (for the cx23885) so we have no
	 * need to attempt to flip bits for earlier av decoders.
	 */
	if (!is_cx2388x(state) && !is_cx231xx(state)) {
		switch (aud_input) {
		case CX25840_AUDIO_SERIAL:
			/* do nothing, use serial audio input */
			break;
		case CX25840_AUDIO4: reg &= ~0x30; break;
		case CX25840_AUDIO5: reg &= ~0x30; reg |= 0x10; break;
		case CX25840_AUDIO6: reg &= ~0x30; reg |= 0x20; break;
		case CX25840_AUDIO7: reg &= ~0xc0; break;
		case CX25840_AUDIO8: reg &= ~0xc0; reg |= 0x40; break;

		default:
			v4l_err(client, "0x%04x is not a valid audio input!\n",
				aud_input);
			return -EINVAL;
		}
	}

	cx25840_write(client, 0x103, reg);

	/* Set INPUT_MODE to Composite, S-Video or Component */
	if (is_component)
		cx25840_and_or(client, 0x401, ~0x6, 0x6);
	else
		cx25840_and_or(client, 0x401, ~0x6, is_composite ? 0 : 0x02);

	if (!is_cx2388x(state) && !is_cx231xx(state)) {
		/* Set CH_SEL_ADC2 to 1 if input comes from CH3 */
		cx25840_and_or(client, 0x102, ~0x2, (reg & 0x80) == 0 ? 2 : 0);
		/* Set DUAL_MODE_ADC2 to 1 if input comes from both CH2&CH3 */
		if ((reg & 0xc0) != 0xc0 && (reg & 0x30) != 0x30)
			cx25840_and_or(client, 0x102, ~0x4, 4);
		else
			cx25840_and_or(client, 0x102, ~0x4, 0);
	} else {
		/* Set DUAL_MODE_ADC2 to 1 if component*/
		cx25840_and_or(client, 0x102, ~0x4, is_component ? 0x4 : 0x0);
		if (is_composite) {
			/* ADC2 input select channel 2 */
			cx25840_and_or(client, 0x102, ~0x2, 0);
		} else if (!is_component) {
			/* S-Video */
			if (chroma >= CX25840_SVIDEO_CHROMA7) {
				/* ADC2 input select channel 3 */
				cx25840_and_or(client, 0x102, ~0x2, 2);
			} else {
				/* ADC2 input select channel 2 */
				cx25840_and_or(client, 0x102, ~0x2, 0);
			}
		}
	}

	state->vid_input = vid_input;
	state->aud_input = aud_input;
	cx25840_audio_set_path(client);
	input_change(client);

	if (is_cx2388x(state)) {
		/* Audio channel 1 src : Parallel 1 */
		cx25840_write(client, 0x124, 0x03);

		/* Select AFE clock pad output source */
		cx25840_write(client, 0x144, 0x05);

		/* I2S_IN_CTL: I2S_IN_SONY_MODE, LEFT SAMPLE on WS=1 */
		cx25840_write(client, 0x914, 0xa0);

		/* I2S_OUT_CTL:
		 * I2S_IN_SONY_MODE, LEFT SAMPLE on WS=1
		 * I2S_OUT_MASTER_MODE = Master
		 */
		cx25840_write(client, 0x918, 0xa0);
		cx25840_write(client, 0x919, 0x01);
	} else if (is_cx231xx(state)) {
		/* Audio channel 1 src : Parallel 1 */
		cx25840_write(client, 0x124, 0x03);

		/* I2S_IN_CTL: I2S_IN_SONY_MODE, LEFT SAMPLE on WS=1 */
		cx25840_write(client, 0x914, 0xa0);

		/* I2S_OUT_CTL:
		 * I2S_IN_SONY_MODE, LEFT SAMPLE on WS=1
		 * I2S_OUT_MASTER_MODE = Master
		 */
		cx25840_write(client, 0x918, 0xa0);
		cx25840_write(client, 0x919, 0x01);
	}

	return 0;
}