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
struct wm8350 {int dummy; } ;
struct snd_soc_codec {struct wm8350* control_data; } ;

/* Variables and functions */
 int wm8350_reg_write (struct wm8350*,unsigned int,unsigned int) ; 

__attribute__((used)) static int wm8350_codec_write(struct snd_soc_codec *codec, unsigned int reg,
			      unsigned int value)
{
	struct wm8350 *wm8350 = codec->control_data;
	return wm8350_reg_write(wm8350, reg, value);
}