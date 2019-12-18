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
struct snd_soc_codec {int (* read ) (struct snd_soc_codec*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write ) (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AD1938_PLL_CLK_CTRL0 ; 
 int AD1938_PLL_POWERDOWN ; 
 int stub1 (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int ad1938_pll_powerctrl(struct snd_soc_codec *codec, int cmd)
{
	int reg = codec->read(codec, AD1938_PLL_CLK_CTRL0);
	reg = (cmd > 0) ? reg & (~AD1938_PLL_POWERDOWN) : reg |
		AD1938_PLL_POWERDOWN;
	codec->write(codec, AD1938_PLL_CLK_CTRL0, reg);

	return 0;
}