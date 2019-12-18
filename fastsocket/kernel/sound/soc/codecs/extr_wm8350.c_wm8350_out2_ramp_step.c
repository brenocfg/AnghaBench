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
typedef  int u16 ;
struct wm8350_output {scalar_t__ ramp; int left_vol; int right_vol; } ;
struct wm8350_data {struct wm8350_output out2; } ;
struct wm8350 {int dummy; } ;
struct snd_soc_codec {struct wm8350* control_data; struct wm8350_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8350_LOUT2_VOLUME ; 
 int WM8350_OUT1L_VOL_SHIFT ; 
 int WM8350_OUT1R_VOL_SHIFT ; 
 int WM8350_OUT2L_VOL_MASK ; 
 int WM8350_OUT2R_VOL_MASK ; 
 int /*<<< orphan*/  WM8350_OUT2_VU ; 
 scalar_t__ WM8350_RAMP_DOWN ; 
 scalar_t__ WM8350_RAMP_UP ; 
 int /*<<< orphan*/  WM8350_ROUT2_VOLUME ; 
 int wm8350_reg_read (struct wm8350*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_reg_write (struct wm8350*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8350_set_bits (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int wm8350_out2_ramp_step(struct snd_soc_codec *codec)
{
	struct wm8350_data *wm8350_data = codec->private_data;
	struct wm8350_output *out2 = &wm8350_data->out2;
	struct wm8350 *wm8350 = codec->control_data;
	int left_complete = 0, right_complete = 0;
	u16 reg, val;

	/* left channel */
	reg = wm8350_reg_read(wm8350, WM8350_LOUT2_VOLUME);
	val = (reg & WM8350_OUT2L_VOL_MASK) >> WM8350_OUT1L_VOL_SHIFT;
	if (out2->ramp == WM8350_RAMP_UP) {
		/* ramp step up */
		if (val < out2->left_vol) {
			val++;
			reg &= ~WM8350_OUT2L_VOL_MASK;
			wm8350_reg_write(wm8350, WM8350_LOUT2_VOLUME,
					 reg | (val << WM8350_OUT1L_VOL_SHIFT));
		} else
			left_complete = 1;
	} else if (out2->ramp == WM8350_RAMP_DOWN) {
		/* ramp step down */
		if (val > 0) {
			val--;
			reg &= ~WM8350_OUT2L_VOL_MASK;
			wm8350_reg_write(wm8350, WM8350_LOUT2_VOLUME,
					 reg | (val << WM8350_OUT1L_VOL_SHIFT));
		} else
			left_complete = 1;
	} else
		return 1;

	/* right channel */
	reg = wm8350_reg_read(wm8350, WM8350_ROUT2_VOLUME);
	val = (reg & WM8350_OUT2R_VOL_MASK) >> WM8350_OUT1R_VOL_SHIFT;
	if (out2->ramp == WM8350_RAMP_UP) {
		/* ramp step up */
		if (val < out2->right_vol) {
			val++;
			reg &= ~WM8350_OUT2R_VOL_MASK;
			wm8350_reg_write(wm8350, WM8350_ROUT2_VOLUME,
					 reg | (val << WM8350_OUT1R_VOL_SHIFT));
		} else
			right_complete = 1;
	} else if (out2->ramp == WM8350_RAMP_DOWN) {
		/* ramp step down */
		if (val > 0) {
			val--;
			reg &= ~WM8350_OUT2R_VOL_MASK;
			wm8350_reg_write(wm8350, WM8350_ROUT2_VOLUME,
					 reg | (val << WM8350_OUT1R_VOL_SHIFT));
		} else
			right_complete = 1;
	}

	/* only hit the update bit if either volume has changed this step */
	if (!left_complete || !right_complete)
		wm8350_set_bits(wm8350, WM8350_LOUT2_VOLUME, WM8350_OUT2_VU);

	return left_complete & right_complete;
}