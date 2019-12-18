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
struct snd_kcontrol {int dummy; } ;
struct snd_ctl_elem_id {int device; int index; int /*<<< orphan*/  name; int /*<<< orphan*/  iface; } ;
struct hda_codec {TYPE_1__* bus; } ;
typedef  int /*<<< orphan*/  id ;
struct TYPE_2__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int /*<<< orphan*/  memset (struct snd_ctl_elem_id*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct snd_kcontrol* snd_ctl_find_id (int /*<<< orphan*/ ,struct snd_ctl_elem_id*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static struct snd_kcontrol *
find_mixer_ctl(struct hda_codec *codec, const char *name, int dev, int idx)
{
	struct snd_ctl_elem_id id;
	memset(&id, 0, sizeof(id));
	id.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	id.device = dev;
	id.index = idx;
	if (snd_BUG_ON(strlen(name) >= sizeof(id.name)))
		return NULL;
	strcpy(id.name, name);
	return snd_ctl_find_id(codec->bus->card, &id);
}