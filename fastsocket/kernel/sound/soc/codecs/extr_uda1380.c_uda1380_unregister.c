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
struct snd_soc_codec {TYPE_1__* dev; } ;
struct uda1380_priv {struct snd_soc_codec codec; } ;
struct uda1380_platform_data {int /*<<< orphan*/  gpio_power; int /*<<< orphan*/  gpio_reset; } ;
struct TYPE_2__ {struct uda1380_platform_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct uda1380_priv*) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  snd_soc_unregister_dais (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * uda1380_codec ; 
 int /*<<< orphan*/  uda1380_dai ; 

__attribute__((used)) static void uda1380_unregister(struct uda1380_priv *uda1380)
{
	struct snd_soc_codec *codec = &uda1380->codec;
	struct uda1380_platform_data *pdata = codec->dev->platform_data;

	snd_soc_unregister_dais(uda1380_dai, ARRAY_SIZE(uda1380_dai));
	snd_soc_unregister_codec(&uda1380->codec);

	gpio_set_value(pdata->gpio_power, 0);
	gpio_free(pdata->gpio_reset);
	gpio_free(pdata->gpio_power);

	kfree(uda1380);
	uda1380_codec = NULL;
}