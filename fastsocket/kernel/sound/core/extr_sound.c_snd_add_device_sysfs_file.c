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
struct snd_card {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int device_create_file (struct device*,struct device_attribute*) ; 
 int find_snd_minor (int,struct snd_card*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__** snd_minors ; 
 int /*<<< orphan*/  sound_mutex ; 

int snd_add_device_sysfs_file(int type, struct snd_card *card, int dev,
			      struct device_attribute *attr)
{
	int minor, ret = -EINVAL;
	struct device *d;

	mutex_lock(&sound_mutex);
	minor = find_snd_minor(type, card, dev);
	if (minor >= 0 && (d = snd_minors[minor]->dev) != NULL)
		ret = device_create_file(d, attr);
	mutex_unlock(&sound_mutex);
	return ret;

}