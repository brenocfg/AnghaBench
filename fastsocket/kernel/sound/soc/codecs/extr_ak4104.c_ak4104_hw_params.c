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
struct snd_soc_pcm_runtime {struct snd_soc_device* socdev; } ;
struct snd_soc_device {TYPE_1__* card; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_soc_codec {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {struct snd_soc_codec* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK4104_REG_CHN_STATUS (int) ; 
 int EINVAL ; 
 int IEC958_AES0_CON_NOT_COPYRIGHT ; 
 int IEC958_AES3_CON_FS_32000 ; 
 int IEC958_AES3_CON_FS_44100 ; 
 int IEC958_AES3_CON_FS_48000 ; 
 int ak4104_spi_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int ak4104_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_device *socdev = rtd->socdev;
	struct snd_soc_codec *codec = socdev->card->codec;
	int val = 0;

	/* set the IEC958 bits: consumer mode, no copyright bit */
	val |= IEC958_AES0_CON_NOT_COPYRIGHT;
	ak4104_spi_write(codec, AK4104_REG_CHN_STATUS(0), val);

	val = 0;

	switch (params_rate(params)) {
	case 44100:
		val |= IEC958_AES3_CON_FS_44100;
		break;
	case 48000:
		val |= IEC958_AES3_CON_FS_48000;
		break;
	case 32000:
		val |= IEC958_AES3_CON_FS_32000;
		break;
	default:
		dev_err(codec->dev, "unsupported sampling rate\n");
		return -EINVAL;
	}

	return ak4104_spi_write(codec, AK4104_REG_CHN_STATUS(3), val);
}