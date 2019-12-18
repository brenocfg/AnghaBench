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
struct snd_soc_codec {int /*<<< orphan*/ * dev; struct i2c_client* control_data; scalar_t__ hw_write; } ;
struct wm8940_priv {struct snd_soc_codec codec; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ hw_write_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SND_SOC_I2C ; 
 scalar_t__ i2c_master_send ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct wm8940_priv*) ; 
 struct wm8940_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wm8940_register (struct wm8940_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8940_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct wm8940_priv *wm8940;
	struct snd_soc_codec *codec;

	wm8940 = kzalloc(sizeof *wm8940, GFP_KERNEL);
	if (wm8940 == NULL)
		return -ENOMEM;

	codec = &wm8940->codec;
	codec->hw_write = (hw_write_t)i2c_master_send;
	i2c_set_clientdata(i2c, wm8940);
	codec->control_data = i2c;
	codec->dev = &i2c->dev;

	return wm8940_register(wm8940, SND_SOC_I2C);
}