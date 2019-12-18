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
struct wm8776_priv {unsigned int* sysclk; } ;
struct snd_soc_dai {size_t id; struct snd_soc_codec* codec; } ;
struct snd_soc_codec {struct wm8776_priv* private_data; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static int wm8776_set_sysclk(struct snd_soc_dai *dai,
			     int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_codec *codec = dai->codec;
	struct wm8776_priv *wm8776 = codec->private_data;

	BUG_ON(dai->id >= ARRAY_SIZE(wm8776->sysclk));

	wm8776->sysclk[dai->id] = freq;

	return 0;
}