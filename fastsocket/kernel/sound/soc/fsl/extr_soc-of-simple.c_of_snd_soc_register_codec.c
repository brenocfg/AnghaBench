#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int dummy; } ;
struct snd_soc_codec_device {int dummy; } ;
struct TYPE_4__ {char* name; char* stream_name; struct snd_soc_dai* codec_dai; } ;
struct TYPE_3__ {struct snd_soc_codec_device* codec_dev; void* codec_data; } ;
struct of_snd_soc_device {TYPE_2__ dai_link; TYPE_1__ device; } ;
struct device_node {scalar_t__ name; int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct of_snd_soc_device* of_snd_soc_get_device (struct device_node*) ; 
 int /*<<< orphan*/  of_snd_soc_mutex ; 
 int /*<<< orphan*/  of_snd_soc_register_device (struct of_snd_soc_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

int of_snd_soc_register_codec(struct snd_soc_codec_device *codec_dev,
			      void *codec_data, struct snd_soc_dai *dai,
			      struct device_node *node)
{
	struct of_snd_soc_device *of_soc;
	int rc = 0;

	pr_info("registering ASoC codec driver: %s\n", node->full_name);

	mutex_lock(&of_snd_soc_mutex);
	of_soc = of_snd_soc_get_device(node);
	if (!of_soc) {
		rc = -ENOMEM;
		goto out;
	}

	/* Store the codec data */
	of_soc->device.codec_data = codec_data;
	of_soc->device.codec_dev = codec_dev;
	of_soc->dai_link.name = (char *)node->name;
	of_soc->dai_link.stream_name = (char *)node->name;
	of_soc->dai_link.codec_dai = dai;

	/* Now try to register the SoC device */
	of_snd_soc_register_device(of_soc);

 out:
	mutex_unlock(&of_snd_soc_mutex);
	return rc;
}