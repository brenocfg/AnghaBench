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
struct wm8580_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  kfree (struct wm8580_priv*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_dais (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wm8580_codec ; 
 int /*<<< orphan*/  wm8580_dai ; 
 int /*<<< orphan*/  wm8580_set_bias_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8580_unregister(struct wm8580_priv *wm8580)
{
	wm8580_set_bias_level(&wm8580->codec, SND_SOC_BIAS_OFF);
	snd_soc_unregister_dais(wm8580_dai, ARRAY_SIZE(wm8580_dai));
	snd_soc_unregister_codec(&wm8580->codec);
	regulator_bulk_disable(ARRAY_SIZE(wm8580->supplies), wm8580->supplies);
	regulator_bulk_free(ARRAY_SIZE(wm8580->supplies), wm8580->supplies);
	kfree(wm8580);
	wm8580_codec = NULL;
}