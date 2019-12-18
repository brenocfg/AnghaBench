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
struct wm8350_data {unsigned int fll_freq_in; unsigned int fll_freq_out; } ;
struct wm8350 {int /*<<< orphan*/  dev; } ;
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {struct wm8350_data* private_data; struct wm8350* control_data; } ;
struct _fll_div {int n; int k; int div; int ratio; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8350_FLL_CONTROL_1 ; 
 int /*<<< orphan*/  WM8350_FLL_CONTROL_2 ; 
 int /*<<< orphan*/  WM8350_FLL_CONTROL_3 ; 
 int /*<<< orphan*/  WM8350_FLL_CONTROL_4 ; 
 int WM8350_FLL_ENA ; 
 int WM8350_FLL_FRAC ; 
 int WM8350_FLL_N_MASK ; 
 int WM8350_FLL_OSC_ENA ; 
 int WM8350_FLL_OUTDIV_MASK ; 
 int WM8350_FLL_RSP_RATE_MASK ; 
 int WM8350_FLL_SLOW_LOCK_REF ; 
 int /*<<< orphan*/  WM8350_POWER_MGMT_4 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,int,int,int,int) ; 
 int fll_factors (struct _fll_div*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wm8350_clear_bits (struct wm8350*,int /*<<< orphan*/ ,int) ; 
 int wm8350_codec_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_codec_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8350_set_bits (struct wm8350*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8350_set_fll(struct snd_soc_dai *codec_dai,
			  int pll_id, unsigned int freq_in,
			  unsigned int freq_out)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct wm8350 *wm8350 = codec->control_data;
	struct wm8350_data *priv = codec->private_data;
	struct _fll_div fll_div;
	int ret = 0;
	u16 fll_1, fll_4;

	if (freq_in == priv->fll_freq_in && freq_out == priv->fll_freq_out)
		return 0;

	/* power down FLL - we need to do this for reconfiguration */
	wm8350_clear_bits(wm8350, WM8350_POWER_MGMT_4,
			  WM8350_FLL_ENA | WM8350_FLL_OSC_ENA);

	if (freq_out == 0 || freq_in == 0)
		return ret;

	ret = fll_factors(&fll_div, freq_in, freq_out);
	if (ret < 0)
		return ret;
	dev_dbg(wm8350->dev,
		"FLL in %u FLL out %u N 0x%x K 0x%x div %d ratio %d",
		freq_in, freq_out, fll_div.n, fll_div.k, fll_div.div,
		fll_div.ratio);

	/* set up N.K & dividers */
	fll_1 = wm8350_codec_read(codec, WM8350_FLL_CONTROL_1) &
	    ~(WM8350_FLL_OUTDIV_MASK | WM8350_FLL_RSP_RATE_MASK | 0xc000);
	wm8350_codec_write(codec, WM8350_FLL_CONTROL_1,
			   fll_1 | (fll_div.div << 8) | 0x50);
	wm8350_codec_write(codec, WM8350_FLL_CONTROL_2,
			   (fll_div.ratio << 11) | (fll_div.
						    n & WM8350_FLL_N_MASK));
	wm8350_codec_write(codec, WM8350_FLL_CONTROL_3, fll_div.k);
	fll_4 = wm8350_codec_read(codec, WM8350_FLL_CONTROL_4) &
	    ~(WM8350_FLL_FRAC | WM8350_FLL_SLOW_LOCK_REF);
	wm8350_codec_write(codec, WM8350_FLL_CONTROL_4,
			   fll_4 | (fll_div.k ? WM8350_FLL_FRAC : 0) |
			   (fll_div.ratio == 8 ? WM8350_FLL_SLOW_LOCK_REF : 0));

	/* power FLL on */
	wm8350_set_bits(wm8350, WM8350_POWER_MGMT_4, WM8350_FLL_OSC_ENA);
	wm8350_set_bits(wm8350, WM8350_POWER_MGMT_4, WM8350_FLL_ENA);

	priv->fll_freq_out = freq_out;
	priv->fll_freq_in = freq_in;

	return 0;
}