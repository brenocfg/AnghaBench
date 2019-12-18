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
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int dummy; } ;
struct _pll_div {int pre_div; int n; int k; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8960_CLOCK1 ; 
 int /*<<< orphan*/  WM8960_PLL1 ; 
 int /*<<< orphan*/  WM8960_PLL2 ; 
 int /*<<< orphan*/  WM8960_PLL3 ; 
 int /*<<< orphan*/  WM8960_PLL4 ; 
 int /*<<< orphan*/  WM8960_POWER2 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int pll_factors (unsigned int,unsigned int,struct _pll_div*) ; 
 int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8960_set_dai_pll(struct snd_soc_dai *codec_dai,
		int pll_id, unsigned int freq_in, unsigned int freq_out)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 reg;
	static struct _pll_div pll_div;
	int ret;

	if (freq_in && freq_out) {
		ret = pll_factors(freq_in, freq_out, &pll_div);
		if (ret != 0)
			return ret;
	}

	/* Disable the PLL: even if we are changing the frequency the
	 * PLL needs to be disabled while we do so. */
	snd_soc_write(codec, WM8960_CLOCK1,
		     snd_soc_read(codec, WM8960_CLOCK1) & ~1);
	snd_soc_write(codec, WM8960_POWER2,
		     snd_soc_read(codec, WM8960_POWER2) & ~1);

	if (!freq_in || !freq_out)
		return 0;

	reg = snd_soc_read(codec, WM8960_PLL1) & ~0x3f;
	reg |= pll_div.pre_div << 4;
	reg |= pll_div.n;

	if (pll_div.k) {
		reg |= 0x20;

		snd_soc_write(codec, WM8960_PLL2, (pll_div.k >> 18) & 0x3f);
		snd_soc_write(codec, WM8960_PLL3, (pll_div.k >> 9) & 0x1ff);
		snd_soc_write(codec, WM8960_PLL4, pll_div.k & 0x1ff);
	}
	snd_soc_write(codec, WM8960_PLL1, reg);

	/* Turn it on */
	snd_soc_write(codec, WM8960_POWER2,
		     snd_soc_read(codec, WM8960_POWER2) | 1);
	msleep(250);
	snd_soc_write(codec, WM8960_CLOCK1,
		     snd_soc_read(codec, WM8960_CLOCK1) | 1);

	return 0;
}