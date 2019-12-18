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
struct wm9081_priv {int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  kfree (struct wm9081_priv*) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_dai (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wm9081_codec ; 
 int /*<<< orphan*/  wm9081_dai ; 
 int /*<<< orphan*/  wm9081_set_bias_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm9081_unregister(struct wm9081_priv *wm9081)
{
	wm9081_set_bias_level(&wm9081->codec, SND_SOC_BIAS_OFF);
	snd_soc_unregister_dai(&wm9081_dai);
	snd_soc_unregister_codec(&wm9081->codec);
	kfree(wm9081);
	wm9081_codec = NULL;
}