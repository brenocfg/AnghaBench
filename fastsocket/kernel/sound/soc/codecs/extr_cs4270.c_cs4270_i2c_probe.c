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
struct snd_soc_codec {char* name; int num_dai; unsigned int (* read ) (struct snd_soc_codec*,int /*<<< orphan*/ ) ;int (* write ) (struct snd_soc_codec*,int /*<<< orphan*/ ,unsigned int) ;int /*<<< orphan*/  reg_cache_size; int /*<<< orphan*/  reg_cache; struct i2c_client* control_data; struct cs4270_private* private_data; TYPE_1__* dai; int /*<<< orphan*/  owner; int /*<<< orphan*/ * dev; int /*<<< orphan*/  dapm_paths; int /*<<< orphan*/  dapm_widgets; int /*<<< orphan*/  mutex; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; } ;
struct cs4270_private {int /*<<< orphan*/  reg_cache; struct snd_soc_codec codec; } ;
struct TYPE_3__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4270_CHIPID ; 
 int /*<<< orphan*/  CS4270_MUTE ; 
 unsigned int CS4270_MUTE_AUTO ; 
 int /*<<< orphan*/  CS4270_NUMREGS ; 
 int /*<<< orphan*/  CS4270_TRANS ; 
 unsigned int CS4270_TRANS_SOFT ; 
 unsigned int CS4270_TRANS_ZERO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct snd_soc_codec* cs4270_codec ; 
 TYPE_1__ cs4270_dai ; 
 int cs4270_fill_cache (struct snd_soc_codec*) ; 
 int cs4270_i2c_write (struct snd_soc_codec*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int cs4270_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct cs4270_private*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cs4270_private*) ; 
 struct cs4270_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_soc_register_dai (TYPE_1__*) ; 

__attribute__((used)) static int cs4270_i2c_probe(struct i2c_client *i2c_client,
	const struct i2c_device_id *id)
{
	struct snd_soc_codec *codec;
	struct cs4270_private *cs4270;
	unsigned int reg;
	int ret;

	/* For now, we only support one cs4270 device in the system.  See the
	 * comment for cs4270_codec.
	 */
	if (cs4270_codec) {
		dev_err(&i2c_client->dev, "ignoring CS4270 at addr %X\n",
		       i2c_client->addr);
		dev_err(&i2c_client->dev, "only one per board allowed\n");
		/* Should we return something other than ENODEV here? */
		return -ENODEV;
	}

	/* Verify that we have a CS4270 */

	ret = i2c_smbus_read_byte_data(i2c_client, CS4270_CHIPID);
	if (ret < 0) {
		dev_err(&i2c_client->dev, "failed to read i2c at addr %X\n",
		       i2c_client->addr);
		return ret;
	}
	/* The top four bits of the chip ID should be 1100. */
	if ((ret & 0xF0) != 0xC0) {
		dev_err(&i2c_client->dev, "device at addr %X is not a CS4270\n",
		       i2c_client->addr);
		return -ENODEV;
	}

	dev_info(&i2c_client->dev, "found device at i2c address %X\n",
		i2c_client->addr);
	dev_info(&i2c_client->dev, "hardware revision %X\n", ret & 0xF);

	/* Allocate enough space for the snd_soc_codec structure
	   and our private data together. */
	cs4270 = kzalloc(sizeof(struct cs4270_private), GFP_KERNEL);
	if (!cs4270) {
		dev_err(&i2c_client->dev, "could not allocate codec\n");
		return -ENOMEM;
	}
	codec = &cs4270->codec;

	mutex_init(&codec->mutex);
	INIT_LIST_HEAD(&codec->dapm_widgets);
	INIT_LIST_HEAD(&codec->dapm_paths);

	codec->dev = &i2c_client->dev;
	codec->name = "CS4270";
	codec->owner = THIS_MODULE;
	codec->dai = &cs4270_dai;
	codec->num_dai = 1;
	codec->private_data = cs4270;
	codec->control_data = i2c_client;
	codec->read = cs4270_read_reg_cache;
	codec->write = cs4270_i2c_write;
	codec->reg_cache = cs4270->reg_cache;
	codec->reg_cache_size = CS4270_NUMREGS;

	/* The I2C interface is set up, so pre-fill our register cache */

	ret = cs4270_fill_cache(codec);
	if (ret < 0) {
		dev_err(&i2c_client->dev, "failed to fill register cache\n");
		goto error_free_codec;
	}

	/* Disable auto-mute.  This feature appears to be buggy.  In some
	 * situations, auto-mute will not deactivate when it should, so we want
	 * this feature disabled by default.  An application (e.g. alsactl) can
	 * re-enabled it by using the controls.
	 */

	reg = cs4270_read_reg_cache(codec, CS4270_MUTE);
	reg &= ~CS4270_MUTE_AUTO;
	ret = cs4270_i2c_write(codec, CS4270_MUTE, reg);
	if (ret < 0) {
		dev_err(&i2c_client->dev, "i2c write failed\n");
		return ret;
	}

	/* Disable automatic volume control.  The hardware enables, and it
	 * causes volume change commands to be delayed, sometimes until after
	 * playback has started.  An application (e.g. alsactl) can
	 * re-enabled it by using the controls.
	 */

	reg = cs4270_read_reg_cache(codec, CS4270_TRANS);
	reg &= ~(CS4270_TRANS_SOFT | CS4270_TRANS_ZERO);
	ret = cs4270_i2c_write(codec, CS4270_TRANS, reg);
	if (ret < 0) {
		dev_err(&i2c_client->dev, "i2c write failed\n");
		return ret;
	}

	/* Initialize the DAI. Normally, we'd prefer to have a kmalloc'd DAI
	 * structure for each CS4270 device, but the machine driver needs to
	 * have a pointer to the DAI structure, so for now it must be a global
	 * variable.
	 */
	cs4270_dai.dev = &i2c_client->dev;

	/* Register the DAI.  If all the other ASoC driver have already
	 * registered, then this will call our probe function, so
	 * cs4270_codec needs to be ready.
	 */
	cs4270_codec = codec;
	ret = snd_soc_register_dai(&cs4270_dai);
	if (ret < 0) {
		dev_err(&i2c_client->dev, "failed to register DAIe\n");
		goto error_free_codec;
	}

	i2c_set_clientdata(i2c_client, cs4270);

	return 0;

error_free_codec:
	kfree(cs4270);
	cs4270_codec = NULL;
	cs4270_dai.dev = NULL;

	return ret;
}