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
struct snd_soc_codec {int /*<<< orphan*/ * dev; scalar_t__ pop_time; int /*<<< orphan*/ * hw_write; int /*<<< orphan*/ * control_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cx20442_priv {struct snd_soc_codec codec; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cx20442_register (struct cx20442_priv*) ; 
 struct cx20442_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cx20442_priv*) ; 

__attribute__((used)) static int cx20442_platform_probe(struct platform_device *pdev)
{
	struct cx20442_priv *cx20442;
	struct snd_soc_codec *codec;

	cx20442 = kzalloc(sizeof(struct cx20442_priv), GFP_KERNEL);
	if (cx20442 == NULL)
		return -ENOMEM;

	codec = &cx20442->codec;

	codec->control_data = NULL;
	codec->hw_write = NULL;
	codec->pop_time = 0;

	codec->dev = &pdev->dev;
	platform_set_drvdata(pdev, cx20442);

	return cx20442_register(cx20442);
}