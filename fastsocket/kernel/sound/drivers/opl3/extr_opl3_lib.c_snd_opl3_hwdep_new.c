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
struct snd_opl3 {int hardware; int seq_dev_num; TYPE_2__* seq_dev; struct snd_hwdep* hwdep; struct snd_card* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/  write; int /*<<< orphan*/  ioctl; int /*<<< orphan*/  open; } ;
struct snd_hwdep {int exclusive; char* name; char* id; TYPE_1__ ops; int /*<<< orphan*/  iface; int /*<<< orphan*/  oss_dev; int /*<<< orphan*/  oss_type; struct snd_opl3* private_data; } ;
struct snd_card {int number; } ;
struct TYPE_5__ {char* name; } ;

/* Variables and functions */
 int OPL3_HW_MASK ; 
#define  OPL3_HW_OPL2 130 
#define  OPL3_HW_OPL3 129 
#define  OPL3_HW_OPL4 128 
 int /*<<< orphan*/  SNDRV_HWDEP_IFACE_OPL2 ; 
 int /*<<< orphan*/  SNDRV_HWDEP_IFACE_OPL3 ; 
 int /*<<< orphan*/  SNDRV_HWDEP_IFACE_OPL4 ; 
 int /*<<< orphan*/  SNDRV_OSS_DEVICE_TYPE_DMFM ; 
 scalar_t__ SNDRV_SEQ_DEVICE_ARGPTR (TYPE_2__*) ; 
 int /*<<< orphan*/  SNDRV_SEQ_DEV_ID_OPL3 ; 
 int /*<<< orphan*/  snd_device_free (struct snd_card*,struct snd_opl3*) ; 
 int snd_hwdep_new (struct snd_card*,char*,int,struct snd_hwdep**) ; 
 int /*<<< orphan*/  snd_opl3_ioctl ; 
 int /*<<< orphan*/  snd_opl3_open ; 
 int /*<<< orphan*/  snd_opl3_release ; 
 int /*<<< orphan*/  snd_opl3_write ; 
 scalar_t__ snd_seq_device_new (struct snd_card*,int,int /*<<< orphan*/ ,int,TYPE_2__**) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int snd_opl3_hwdep_new(struct snd_opl3 * opl3,
		       int device, int seq_device,
		       struct snd_hwdep ** rhwdep)
{
	struct snd_hwdep *hw;
	struct snd_card *card = opl3->card;
	int err;

	if (rhwdep)
		*rhwdep = NULL;

	/* create hardware dependent device (direct FM) */

	if ((err = snd_hwdep_new(card, "OPL2/OPL3", device, &hw)) < 0) {
		snd_device_free(card, opl3);
		return err;
	}
	hw->private_data = opl3;
	hw->exclusive = 1;
#ifdef CONFIG_SND_OSSEMUL
	if (device == 0) {
		hw->oss_type = SNDRV_OSS_DEVICE_TYPE_DMFM;
		sprintf(hw->oss_dev, "dmfm%i", card->number);
	}
#endif
	strcpy(hw->name, hw->id);
	switch (opl3->hardware & OPL3_HW_MASK) {
	case OPL3_HW_OPL2:
		strcpy(hw->name, "OPL2 FM");
		hw->iface = SNDRV_HWDEP_IFACE_OPL2;
		break;
	case OPL3_HW_OPL3:
		strcpy(hw->name, "OPL3 FM");
		hw->iface = SNDRV_HWDEP_IFACE_OPL3;
		break;
	case OPL3_HW_OPL4:
		strcpy(hw->name, "OPL4 FM");
		hw->iface = SNDRV_HWDEP_IFACE_OPL4;
		break;
	}

	/* operators - only ioctl */
	hw->ops.open = snd_opl3_open;
	hw->ops.ioctl = snd_opl3_ioctl;
	hw->ops.write = snd_opl3_write;
	hw->ops.release = snd_opl3_release;

	opl3->hwdep = hw;
	opl3->seq_dev_num = seq_device;
#if defined(CONFIG_SND_SEQUENCER) || (defined(MODULE) && defined(CONFIG_SND_SEQUENCER_MODULE))
	if (snd_seq_device_new(card, seq_device, SNDRV_SEQ_DEV_ID_OPL3,
			       sizeof(struct snd_opl3 *), &opl3->seq_dev) >= 0) {
		strcpy(opl3->seq_dev->name, hw->name);
		*(struct snd_opl3 **)SNDRV_SEQ_DEVICE_ARGPTR(opl3->seq_dev) = opl3;
	}
#endif
	if (rhwdep)
		*rhwdep = hw;
	return 0;
}