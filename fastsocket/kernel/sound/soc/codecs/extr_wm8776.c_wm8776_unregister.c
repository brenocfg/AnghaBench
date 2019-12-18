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
struct wm8776_priv {int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  kfree (struct wm8776_priv*) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_dais (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wm8776_codec ; 
 int /*<<< orphan*/  wm8776_dai ; 
 int /*<<< orphan*/  wm8776_set_bias_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8776_unregister(struct wm8776_priv *wm8776)
{
	wm8776_set_bias_level(&wm8776->codec, SND_SOC_BIAS_OFF);
	snd_soc_unregister_dais(wm8776_dai, ARRAY_SIZE(wm8776_dai));
	snd_soc_unregister_codec(&wm8776->codec);
	kfree(wm8776);
	wm8776_codec = NULL;
}