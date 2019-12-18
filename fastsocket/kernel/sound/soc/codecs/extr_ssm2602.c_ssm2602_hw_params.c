#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct ssm2602_priv {struct snd_pcm_substream* slave_substream; int /*<<< orphan*/  sysclk; } ;
struct snd_soc_pcm_runtime {struct snd_soc_device* socdev; } ;
struct snd_soc_device {TYPE_1__* card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_codec {struct i2c_client* control_data; struct ssm2602_priv* private_data; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int sr; int bosr; int usb; } ;
struct TYPE_4__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int ACTIVE_ACTIVATE_CODEC ; 
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
#define  SNDRV_PCM_FORMAT_S16_LE 131 
#define  SNDRV_PCM_FORMAT_S20_3LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 
 int /*<<< orphan*/  SSM2602_ACTIVE ; 
 int /*<<< orphan*/  SSM2602_IFACE ; 
 int /*<<< orphan*/  SSM2602_SRATE ; 
 TYPE_2__* coeff_div ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int get_coeff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int ssm2602_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssm2602_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ssm2602_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params,
	struct snd_soc_dai *dai)
{
	u16 srate;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_device *socdev = rtd->socdev;
	struct snd_soc_codec *codec = socdev->card->codec;
	struct ssm2602_priv *ssm2602 = codec->private_data;
	struct i2c_client *i2c = codec->control_data;
	u16 iface = ssm2602_read_reg_cache(codec, SSM2602_IFACE) & 0xfff3;
	int i = get_coeff(ssm2602->sysclk, params_rate(params));

	if (substream == ssm2602->slave_substream) {
		dev_dbg(&i2c->dev, "Ignoring hw_params for slave substream\n");
		return 0;
	}

	/*no match is found*/
	if (i == ARRAY_SIZE(coeff_div))
		return -EINVAL;

	srate = (coeff_div[i].sr << 2) |
		(coeff_div[i].bosr << 1) | coeff_div[i].usb;

	ssm2602_write(codec, SSM2602_ACTIVE, 0);
	ssm2602_write(codec, SSM2602_SRATE, srate);

	/* bit size */
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		iface |= 0x0004;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		iface |= 0x0008;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		iface |= 0x000c;
		break;
	}
	ssm2602_write(codec, SSM2602_IFACE, iface);
	ssm2602_write(codec, SSM2602_ACTIVE, ACTIVE_ACTIVATE_CODEC);
	return 0;
}