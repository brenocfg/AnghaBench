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
struct ssm2602_setup_data {scalar_t__ i2c_address; } ;
struct ssm2602_priv {int dummy; } ;
struct snd_soc_device {TYPE_1__* card; struct ssm2602_setup_data* codec_data; } ;
struct snd_soc_codec {scalar_t__ hw_write; int /*<<< orphan*/  dapm_paths; int /*<<< orphan*/  dapm_widgets; int /*<<< orphan*/  mutex; struct ssm2602_priv* private_data; } ;
struct platform_device {int dummy; } ;
typedef  scalar_t__ hw_write_t ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSM2602_VERSION ; 
 scalar_t__ i2c_master_send ; 
 int /*<<< orphan*/  kfree (struct snd_soc_codec*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct snd_soc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int ssm2602_add_i2c_device (struct platform_device*,struct ssm2602_setup_data*) ; 
 struct snd_soc_device* ssm2602_socdev ; 

__attribute__((used)) static int ssm2602_probe(struct platform_device *pdev)
{
	struct snd_soc_device *socdev = platform_get_drvdata(pdev);
	struct ssm2602_setup_data *setup;
	struct snd_soc_codec *codec;
	struct ssm2602_priv *ssm2602;
	int ret = 0;

	pr_info("ssm2602 Audio Codec %s", SSM2602_VERSION);

	setup = socdev->codec_data;
	codec = kzalloc(sizeof(struct snd_soc_codec), GFP_KERNEL);
	if (codec == NULL)
		return -ENOMEM;

	ssm2602 = kzalloc(sizeof(struct ssm2602_priv), GFP_KERNEL);
	if (ssm2602 == NULL) {
		kfree(codec);
		return -ENOMEM;
	}

	codec->private_data = ssm2602;
	socdev->card->codec = codec;
	mutex_init(&codec->mutex);
	INIT_LIST_HEAD(&codec->dapm_widgets);
	INIT_LIST_HEAD(&codec->dapm_paths);

	ssm2602_socdev = socdev;
#if defined(CONFIG_I2C) || defined(CONFIG_I2C_MODULE)
	if (setup->i2c_address) {
		codec->hw_write = (hw_write_t)i2c_master_send;
		ret = ssm2602_add_i2c_device(pdev, setup);
	}
#else
	/* other interfaces */
#endif
	return ret;
}