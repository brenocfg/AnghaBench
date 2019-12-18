#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  delayed_work; } ;
struct wm8753_priv {TYPE_1__ codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  kfree (struct wm8753_priv*) ; 
 int /*<<< orphan*/  run_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_soc_unregister_dais (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wm8753_codec ; 
 int /*<<< orphan*/ * wm8753_dai ; 
 int /*<<< orphan*/  wm8753_set_bias_level (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wm8753_unregister(struct wm8753_priv *wm8753)
{
	wm8753_set_bias_level(&wm8753->codec, SND_SOC_BIAS_OFF);
	run_delayed_work(&wm8753->codec.delayed_work);
	snd_soc_unregister_dais(&wm8753_dai[0], ARRAY_SIZE(wm8753_dai));
	snd_soc_unregister_codec(&wm8753->codec);
	kfree(wm8753);
	wm8753_codec = NULL;
}