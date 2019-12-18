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
struct snd_rawmidi_file {int dummy; } ;
struct snd_rawmidi {TYPE_1__* card; int /*<<< orphan*/  open_mutex; } ;
struct snd_card {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rawmidi_open_priv (struct snd_rawmidi*,int,int,struct snd_rawmidi_file*) ; 
 int /*<<< orphan*/  register_mutex ; 
 scalar_t__ snd_BUG_ON (int) ; 
 struct snd_rawmidi* snd_rawmidi_search (struct snd_card*,int) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int snd_rawmidi_kernel_open(struct snd_card *card, int device, int subdevice,
			    int mode, struct snd_rawmidi_file * rfile)
{
	struct snd_rawmidi *rmidi;
	int err;

	if (snd_BUG_ON(!rfile))
		return -EINVAL;

	mutex_lock(&register_mutex);
	rmidi = snd_rawmidi_search(card, device);
	if (rmidi == NULL) {
		mutex_unlock(&register_mutex);
		return -ENODEV;
	}
	if (!try_module_get(rmidi->card->module)) {
		mutex_unlock(&register_mutex);
		return -ENXIO;
	}
	mutex_unlock(&register_mutex);

	mutex_lock(&rmidi->open_mutex);
	err = rawmidi_open_priv(rmidi, subdevice, mode, rfile);
	mutex_unlock(&rmidi->open_mutex);
	if (err < 0)
		module_put(rmidi->card->module);
	return err;
}