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
struct snd_soc_codec {char* name; int num_dai; int /*<<< orphan*/  dev; int /*<<< orphan*/  bias_level; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  reg_cache_size; int /*<<< orphan*/ * reg_cache; TYPE_1__* dai; struct cx20442_priv* private_data; int /*<<< orphan*/  owner; int /*<<< orphan*/  dapm_paths; int /*<<< orphan*/  dapm_widgets; int /*<<< orphan*/  mutex; } ;
struct cx20442_priv {int /*<<< orphan*/  reg_cache; struct snd_soc_codec codec; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct snd_soc_codec* cx20442_codec ; 
 TYPE_1__ cx20442_dai ; 
 int /*<<< orphan*/  cx20442_read_reg_cache ; 
 int /*<<< orphan*/  cx20442_write ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (struct cx20442_priv*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_soc_register_codec (struct snd_soc_codec*) ; 
 int snd_soc_register_dai (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (struct snd_soc_codec*) ; 

__attribute__((used)) static int cx20442_register(struct cx20442_priv *cx20442)
{
	struct snd_soc_codec *codec = &cx20442->codec;
	int ret;

	mutex_init(&codec->mutex);
	INIT_LIST_HEAD(&codec->dapm_widgets);
	INIT_LIST_HEAD(&codec->dapm_paths);

	codec->name = "CX20442";
	codec->owner = THIS_MODULE;
	codec->private_data = cx20442;

	codec->dai = &cx20442_dai;
	codec->num_dai = 1;

	codec->reg_cache = &cx20442->reg_cache;
	codec->reg_cache_size = ARRAY_SIZE(cx20442->reg_cache);
	codec->read = cx20442_read_reg_cache;
	codec->write = cx20442_write;

	codec->bias_level = SND_SOC_BIAS_OFF;

	cx20442_dai.dev = codec->dev;

	cx20442_codec = codec;

	ret = snd_soc_register_codec(codec);
	if (ret != 0) {
		dev_err(codec->dev, "Failed to register codec: %d\n", ret);
		goto err;
	}

	ret = snd_soc_register_dai(&cx20442_dai);
	if (ret != 0) {
		dev_err(codec->dev, "Failed to register DAI: %d\n", ret);
		goto err_codec;
	}

	return 0;

err_codec:
	snd_soc_unregister_codec(codec);
err:
	cx20442_codec = NULL;
	kfree(cx20442);
	return ret;
}