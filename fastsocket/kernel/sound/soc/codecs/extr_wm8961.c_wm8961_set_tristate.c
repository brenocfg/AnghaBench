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
typedef  int /*<<< orphan*/  u16 ;
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8961_ADDITIONAL_CONTROL_2 ; 
 int /*<<< orphan*/  WM8961_TRIS ; 
 int /*<<< orphan*/  snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8961_set_tristate(struct snd_soc_dai *dai, int tristate)
{
	struct snd_soc_codec *codec = dai->codec;
	u16 reg = snd_soc_read(codec, WM8961_ADDITIONAL_CONTROL_2);

	if (tristate)
		reg |= WM8961_TRIS;
	else
		reg &= ~WM8961_TRIS;

	return snd_soc_write(codec, WM8961_ADDITIONAL_CONTROL_2, reg);
}