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
struct wm8960_priv {int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  kfree (struct wm8960_priv*) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_dai (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wm8960_codec ; 
 int /*<<< orphan*/  wm8960_dai ; 
 int /*<<< orphan*/  wm8960_set_bias_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8960_unregister(struct wm8960_priv *wm8960)
{
	wm8960_set_bias_level(&wm8960->codec, SND_SOC_BIAS_OFF);
	snd_soc_unregister_dai(&wm8960_dai);
	snd_soc_unregister_codec(&wm8960->codec);
	kfree(wm8960);
	wm8960_codec = NULL;
}