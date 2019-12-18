#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_14__ {TYPE_1__ archdata; } ;
struct spi_device {TYPE_4__ dev; } ;
struct TYPE_15__ {char* name; int num_dai; int (* read ) (TYPE_9__*,int) ;int /*<<< orphan*/  reg_cache; int /*<<< orphan*/  reg_cache_size; int /*<<< orphan*/  dapm_paths; int /*<<< orphan*/  dapm_widgets; int /*<<< orphan*/  mutex; int /*<<< orphan*/  (* write ) (TYPE_9__*,int,int) ;TYPE_2__* dai; int /*<<< orphan*/  owner; struct aic26* private_data; } ;
struct aic26 {int master; TYPE_9__ codec; int /*<<< orphan*/  reg_cache; struct spi_device* spi; } ;
struct TYPE_13__ {TYPE_4__* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC26_NUM_REGS ; 
 int AIC26_REG_AUDIO_CTRL3 ; 
 int AIC26_REG_POWER_CTRL ; 
 int AIC26_REG_RESET ; 
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 TYPE_2__ aic26_dai ; 
 int aic26_reg_read (TYPE_9__*,int) ; 
 int /*<<< orphan*/  aic26_reg_write (TYPE_9__*,int,int) ; 
 int /*<<< orphan*/  aic26_soc_codec_dev ; 
 int /*<<< orphan*/  dev_attr_keyclick ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_4__*,struct aic26*) ; 
 int device_create_file (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct aic26*) ; 
 struct aic26* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_snd_soc_register_codec (int /*<<< orphan*/ *,struct aic26*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int snd_soc_register_dai (TYPE_2__*) ; 

__attribute__((used)) static int aic26_spi_probe(struct spi_device *spi)
{
	struct aic26 *aic26;
	int ret, i, reg;

	dev_dbg(&spi->dev, "probing tlv320aic26 spi device\n");

	/* Allocate driver data */
	aic26 = kzalloc(sizeof *aic26, GFP_KERNEL);
	if (!aic26)
		return -ENOMEM;

	/* Initialize the driver data */
	aic26->spi = spi;
	dev_set_drvdata(&spi->dev, aic26);

	/* Setup what we can in the codec structure so that the register
	 * access functions will work as expected.  More will be filled
	 * out when it is probed by the SoC CODEC part of this driver */
	aic26->codec.private_data = aic26;
	aic26->codec.name = "aic26";
	aic26->codec.owner = THIS_MODULE;
	aic26->codec.dai = &aic26_dai;
	aic26->codec.num_dai = 1;
	aic26->codec.read = aic26_reg_read;
	aic26->codec.write = aic26_reg_write;
	aic26->master = 1;
	mutex_init(&aic26->codec.mutex);
	INIT_LIST_HEAD(&aic26->codec.dapm_widgets);
	INIT_LIST_HEAD(&aic26->codec.dapm_paths);
	aic26->codec.reg_cache_size = AIC26_NUM_REGS;
	aic26->codec.reg_cache = aic26->reg_cache;

	aic26_dai.dev = &spi->dev;
	ret = snd_soc_register_dai(&aic26_dai);
	if (ret != 0) {
		dev_err(&spi->dev, "Failed to register DAI: %d\n", ret);
		kfree(aic26);
		return ret;
	}

	/* Reset the codec to power on defaults */
	aic26_reg_write(&aic26->codec, AIC26_REG_RESET, 0xBB00);

	/* Power up CODEC */
	aic26_reg_write(&aic26->codec, AIC26_REG_POWER_CTRL, 0);

	/* Audio Control 3 (master mode, fsref rate) */
	reg = aic26_reg_read(&aic26->codec, AIC26_REG_AUDIO_CTRL3);
	reg &= ~0xf800;
	reg |= 0x0800; /* set master mode */
	aic26_reg_write(&aic26->codec, AIC26_REG_AUDIO_CTRL3, reg);

	/* Fill register cache */
	for (i = 0; i < ARRAY_SIZE(aic26->reg_cache); i++)
		aic26_reg_read(&aic26->codec, i);

	/* Register the sysfs files for debugging */
	/* Create SysFS files */
	ret = device_create_file(&spi->dev, &dev_attr_keyclick);
	if (ret)
		dev_info(&spi->dev, "error creating sysfs files\n");

#if defined(CONFIG_SND_SOC_OF_SIMPLE)
	/* Tell the of_soc helper about this codec */
	of_snd_soc_register_codec(&aic26_soc_codec_dev, aic26, &aic26_dai,
				  spi->dev.archdata.of_node);
#endif

	dev_dbg(&spi->dev, "SPI device initialized\n");
	return 0;
}