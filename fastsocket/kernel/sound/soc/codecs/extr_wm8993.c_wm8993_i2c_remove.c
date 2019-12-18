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
struct wm8993_priv {int /*<<< orphan*/  codec; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 struct wm8993_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct wm8993_priv*) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_dai (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wm8993_dai ; 
 int /*<<< orphan*/  wm8993_set_bias_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8993_i2c_remove(struct i2c_client *client)
{
	struct wm8993_priv *wm8993 = i2c_get_clientdata(client);

	snd_soc_unregister_codec(&wm8993->codec);
	snd_soc_unregister_dai(&wm8993_dai);

	wm8993_set_bias_level(&wm8993->codec, SND_SOC_BIAS_OFF);
	kfree(wm8993);

	return 0;
}