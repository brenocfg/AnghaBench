#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wm8990_setup_data {scalar_t__ i2c_address; } ;
struct wm8990_priv {struct wm8990_priv* private_data; scalar_t__ hw_write; int /*<<< orphan*/  dapm_paths; int /*<<< orphan*/  dapm_widgets; int /*<<< orphan*/  mutex; } ;
struct snd_soc_device {TYPE_1__* card; struct wm8990_setup_data* codec_data; } ;
struct snd_soc_codec {struct snd_soc_codec* private_data; scalar_t__ hw_write; int /*<<< orphan*/  dapm_paths; int /*<<< orphan*/  dapm_widgets; int /*<<< orphan*/  mutex; } ;
struct platform_device {int dummy; } ;
typedef  scalar_t__ hw_write_t ;
struct TYPE_2__ {struct wm8990_priv* codec; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WM8990_VERSION ; 
 scalar_t__ i2c_master_send ; 
 int /*<<< orphan*/  kfree (struct wm8990_priv*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct snd_soc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int wm8990_add_i2c_device (struct platform_device*,struct wm8990_setup_data*) ; 
 struct snd_soc_device* wm8990_socdev ; 

__attribute__((used)) static int wm8990_probe(struct platform_device *pdev)
{
	struct snd_soc_device *socdev = platform_get_drvdata(pdev);
	struct wm8990_setup_data *setup;
	struct snd_soc_codec *codec;
	struct wm8990_priv *wm8990;
	int ret;

	pr_info("WM8990 Audio Codec %s\n", WM8990_VERSION);

	setup = socdev->codec_data;
	codec = kzalloc(sizeof(struct snd_soc_codec), GFP_KERNEL);
	if (codec == NULL)
		return -ENOMEM;

	wm8990 = kzalloc(sizeof(struct wm8990_priv), GFP_KERNEL);
	if (wm8990 == NULL) {
		kfree(codec);
		return -ENOMEM;
	}

	codec->private_data = wm8990;
	socdev->card->codec = codec;
	mutex_init(&codec->mutex);
	INIT_LIST_HEAD(&codec->dapm_widgets);
	INIT_LIST_HEAD(&codec->dapm_paths);
	wm8990_socdev = socdev;

	ret = -ENODEV;

#if defined(CONFIG_I2C) || defined(CONFIG_I2C_MODULE)
	if (setup->i2c_address) {
		codec->hw_write = (hw_write_t)i2c_master_send;
		ret = wm8990_add_i2c_device(pdev, setup);
	}
#endif

	if (ret != 0) {
		kfree(codec->private_data);
		kfree(codec);
	}
	return ret;
}