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
struct wm8400_priv {int /*<<< orphan*/  wm8400; } ;
struct snd_soc_codec {struct wm8400_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  wm8400_reset_codec_reg_cache (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8400_codec_reset(struct snd_soc_codec *codec)
{
	struct wm8400_priv *wm8400 = codec->private_data;

	wm8400_reset_codec_reg_cache(wm8400->wm8400);
}