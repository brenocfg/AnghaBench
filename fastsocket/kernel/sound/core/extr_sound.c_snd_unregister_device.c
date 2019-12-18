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
struct snd_card {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int find_snd_minor (int,struct snd_card*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  major ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** snd_minors ; 
 int /*<<< orphan*/  sound_class ; 
 int /*<<< orphan*/  sound_mutex ; 

int snd_unregister_device(int type, struct snd_card *card, int dev)
{
	int minor;

	mutex_lock(&sound_mutex);
	minor = find_snd_minor(type, card, dev);
	if (minor < 0) {
		mutex_unlock(&sound_mutex);
		return -EINVAL;
	}

	device_destroy(sound_class, MKDEV(major, minor));

	kfree(snd_minors[minor]);
	snd_minors[minor] = NULL;
	mutex_unlock(&sound_mutex);
	return 0;
}