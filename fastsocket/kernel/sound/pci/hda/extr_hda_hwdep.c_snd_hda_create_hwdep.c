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
struct TYPE_4__ {int /*<<< orphan*/  ioctl_compat; int /*<<< orphan*/  ioctl; int /*<<< orphan*/  open; } ;
struct snd_hwdep {char* name; int exclusive; TYPE_2__ ops; int /*<<< orphan*/  private_free; struct hda_codec* private_data; int /*<<< orphan*/  iface; } ;
struct hda_verb {int dummy; } ;
struct hda_pincfg {int dummy; } ;
struct hda_hint {int dummy; } ;
struct hda_codec {int addr; int /*<<< orphan*/  user_pins; int /*<<< orphan*/  hints; int /*<<< orphan*/  init_verbs; int /*<<< orphan*/  user_mutex; struct snd_hwdep* hwdep; TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_HWDEP_IFACE_HDA ; 
 int /*<<< orphan*/  hda_hwdep_ioctl ; 
 int /*<<< orphan*/  hda_hwdep_ioctl_compat ; 
 int /*<<< orphan*/  hda_hwdep_open ; 
 int /*<<< orphan*/  hwdep_free ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_array_init (int /*<<< orphan*/ *,int,int) ; 
 int snd_hwdep_new (int /*<<< orphan*/ ,char*,int,struct snd_hwdep**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

int snd_hda_create_hwdep(struct hda_codec *codec)
{
	char hwname[16];
	struct snd_hwdep *hwdep;
	int err;

	sprintf(hwname, "HDA Codec %d", codec->addr);
	err = snd_hwdep_new(codec->bus->card, hwname, codec->addr, &hwdep);
	if (err < 0)
		return err;
	codec->hwdep = hwdep;
	sprintf(hwdep->name, "HDA Codec %d", codec->addr);
	hwdep->iface = SNDRV_HWDEP_IFACE_HDA;
	hwdep->private_data = codec;
	hwdep->private_free = hwdep_free;
	hwdep->exclusive = 1;

	hwdep->ops.open = hda_hwdep_open;
	hwdep->ops.ioctl = hda_hwdep_ioctl;
#ifdef CONFIG_COMPAT
	hwdep->ops.ioctl_compat = hda_hwdep_ioctl_compat;
#endif

	mutex_init(&codec->user_mutex);
	snd_array_init(&codec->init_verbs, sizeof(struct hda_verb), 32);
	snd_array_init(&codec->hints, sizeof(struct hda_hint), 32);
	snd_array_init(&codec->user_pins, sizeof(struct hda_pincfg), 16);

	return 0;
}