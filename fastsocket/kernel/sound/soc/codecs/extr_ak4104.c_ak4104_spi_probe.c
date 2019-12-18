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
struct spi_device {int bits_per_word; int /*<<< orphan*/  dev; int /*<<< orphan*/  mode; } ;
struct snd_soc_codec {int num_dai; int /*<<< orphan*/  reg_cache_size; int /*<<< orphan*/  reg_cache; struct spi_device* control_data; struct ak4104_private* private_data; TYPE_1__* dai; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; int /*<<< orphan*/ * dev; int /*<<< orphan*/  dapm_paths; int /*<<< orphan*/  dapm_widgets; int /*<<< orphan*/  mutex; } ;
struct ak4104_private {int /*<<< orphan*/  reg_cache; struct snd_soc_codec codec; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int AK4104_CONTROL1_PW ; 
 int AK4104_CONTROL1_RSTN ; 
 int /*<<< orphan*/  AK4104_NUM_REGS ; 
 int /*<<< orphan*/  AK4104_REG_CONTROL1 ; 
 int /*<<< orphan*/  AK4104_REG_RESERVED ; 
 int /*<<< orphan*/  AK4104_REG_TX ; 
 int AK4104_RESERVED_VAL ; 
 int AK4104_TX_TXE ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct snd_soc_codec* ak4104_codec ; 
 TYPE_1__ ak4104_dai ; 
 int ak4104_fill_cache (struct snd_soc_codec*) ; 
 int ak4104_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int ak4104_spi_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct ak4104_private*) ; 
 struct ak4104_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_soc_register_dai (TYPE_1__*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct ak4104_private*) ; 
 int spi_setup (struct spi_device*) ; 

__attribute__((used)) static int ak4104_spi_probe(struct spi_device *spi)
{
	struct snd_soc_codec *codec;
	struct ak4104_private *ak4104;
	int ret, val;

	spi->bits_per_word = 8;
	spi->mode = SPI_MODE_0;
	ret = spi_setup(spi);
	if (ret < 0)
		return ret;

	ak4104 = kzalloc(sizeof(struct ak4104_private), GFP_KERNEL);
	if (!ak4104) {
		dev_err(&spi->dev, "could not allocate codec\n");
		return -ENOMEM;
	}

	codec = &ak4104->codec;
	mutex_init(&codec->mutex);
	INIT_LIST_HEAD(&codec->dapm_widgets);
	INIT_LIST_HEAD(&codec->dapm_paths);

	codec->dev = &spi->dev;
	codec->name = DRV_NAME;
	codec->owner = THIS_MODULE;
	codec->dai = &ak4104_dai;
	codec->num_dai = 1;
	codec->private_data = ak4104;
	codec->control_data = spi;
	codec->reg_cache = ak4104->reg_cache;
	codec->reg_cache_size = AK4104_NUM_REGS;

	/* read all regs and fill the cache */
	ret = ak4104_fill_cache(codec);
	if (ret < 0) {
		dev_err(&spi->dev, "failed to fill register cache\n");
		return ret;
	}

	/* read the 'reserved' register - according to the datasheet, it
	 * should contain 0x5b. Not a good way to verify the presence of
	 * the device, but there is no hardware ID register. */
	if (ak4104_read_reg_cache(codec, AK4104_REG_RESERVED) !=
					 AK4104_RESERVED_VAL) {
		ret = -ENODEV;
		goto error_free_codec;
	}

	/* set power-up and non-reset bits */
	val = ak4104_read_reg_cache(codec, AK4104_REG_CONTROL1);
	val |= AK4104_CONTROL1_PW | AK4104_CONTROL1_RSTN;
	ret = ak4104_spi_write(codec, AK4104_REG_CONTROL1, val);
	if (ret < 0)
		goto error_free_codec;

	/* enable transmitter */
	val = ak4104_read_reg_cache(codec, AK4104_REG_TX);
	val |= AK4104_TX_TXE;
	ret = ak4104_spi_write(codec, AK4104_REG_TX, val);
	if (ret < 0)
		goto error_free_codec;

	ak4104_codec = codec;
	ret = snd_soc_register_dai(&ak4104_dai);
	if (ret < 0) {
		dev_err(&spi->dev, "failed to register DAI\n");
		goto error_free_codec;
	}

	spi_set_drvdata(spi, ak4104);
	dev_info(&spi->dev, "SPI device initialized\n");
	return 0;

error_free_codec:
	kfree(ak4104);
	ak4104_dai.dev = NULL;
	return ret;
}