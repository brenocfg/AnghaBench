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
struct wm8523_priv {int /*<<< orphan*/  codec; int /*<<< orphan*/  supplies; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  kfree (struct wm8523_priv*) ; 
 int /*<<< orphan*/  regulator_bulk_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_dai (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wm8523_codec ; 
 int /*<<< orphan*/  wm8523_dai ; 
 int /*<<< orphan*/  wm8523_set_bias_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8523_unregister(struct wm8523_priv *wm8523)
{
	wm8523_set_bias_level(&wm8523->codec, SND_SOC_BIAS_OFF);
	regulator_bulk_free(ARRAY_SIZE(wm8523->supplies), wm8523->supplies);
	snd_soc_unregister_dai(&wm8523_dai);
	snd_soc_unregister_codec(&wm8523->codec);
	kfree(wm8523);
	wm8523_codec = NULL;
}