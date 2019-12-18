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
struct snd_seq_oss_reg {struct snd_opl3* private_data; int /*<<< orphan*/  oper; int /*<<< orphan*/  nvoices; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;
struct snd_seq_device {int /*<<< orphan*/  name; } ;
struct snd_opl3 {scalar_t__ hardware; int /*<<< orphan*/  card; struct snd_seq_device* oss_seq_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_TYPE_ADLIB ; 
 int /*<<< orphan*/  FM_TYPE_OPL3 ; 
 int /*<<< orphan*/  MAX_OPL2_VOICES ; 
 int /*<<< orphan*/  MAX_OPL3_VOICES ; 
 scalar_t__ OPL3_HW_OPL3 ; 
 struct snd_seq_oss_reg* SNDRV_SEQ_DEVICE_ARGPTR (struct snd_seq_device*) ; 
 int /*<<< orphan*/  SNDRV_SEQ_DEV_ID_OSS ; 
 int /*<<< orphan*/  SYNTH_TYPE_FM ; 
 int /*<<< orphan*/  oss_callback ; 
 int /*<<< orphan*/  snd_device_register (int /*<<< orphan*/ ,struct snd_seq_device*) ; 
 scalar_t__ snd_opl3_oss_create_port (struct snd_opl3*) ; 
 scalar_t__ snd_seq_device_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct snd_seq_device**) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

void snd_opl3_init_seq_oss(struct snd_opl3 *opl3, char *name)
{
	struct snd_seq_oss_reg *arg;
	struct snd_seq_device *dev;

	if (snd_seq_device_new(opl3->card, 0, SNDRV_SEQ_DEV_ID_OSS,
			       sizeof(struct snd_seq_oss_reg), &dev) < 0)
		return;

	opl3->oss_seq_dev = dev;
	strlcpy(dev->name, name, sizeof(dev->name));
	arg = SNDRV_SEQ_DEVICE_ARGPTR(dev);
	arg->type = SYNTH_TYPE_FM;
	if (opl3->hardware < OPL3_HW_OPL3) {
		arg->subtype = FM_TYPE_ADLIB;
		arg->nvoices = MAX_OPL2_VOICES;
	} else {
		arg->subtype = FM_TYPE_OPL3;
		arg->nvoices = MAX_OPL3_VOICES;
	}
	arg->oper = oss_callback;
	arg->private_data = opl3;

	if (snd_opl3_oss_create_port(opl3)) {
		/* register to OSS synth table */
		snd_device_register(opl3->card, dev);
	}
}