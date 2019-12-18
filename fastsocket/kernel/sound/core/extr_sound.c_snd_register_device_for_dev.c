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
struct snd_minor {int type; int card; int device; int /*<<< orphan*/  dev; void* private_data; struct file_operations const* f_ops; } ;
struct snd_card {int number; } ;
struct file_operations {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,void*,char*,char const*) ; 
 int /*<<< orphan*/  kfree (struct snd_minor*) ; 
 struct snd_minor* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  major ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_find_free_minor () ; 
 int snd_kernel_minor (int,struct snd_card*,int) ; 
 struct snd_minor** snd_minors ; 
 int /*<<< orphan*/  sound_class ; 
 int /*<<< orphan*/  sound_mutex ; 

int snd_register_device_for_dev(int type, struct snd_card *card, int dev,
				const struct file_operations *f_ops,
				void *private_data,
				const char *name, struct device *device)
{
	int minor;
	struct snd_minor *preg;

	if (snd_BUG_ON(!name))
		return -EINVAL;
	preg = kmalloc(sizeof *preg, GFP_KERNEL);
	if (preg == NULL)
		return -ENOMEM;
	preg->type = type;
	preg->card = card ? card->number : -1;
	preg->device = dev;
	preg->f_ops = f_ops;
	preg->private_data = private_data;
	mutex_lock(&sound_mutex);
#ifdef CONFIG_SND_DYNAMIC_MINORS
	minor = snd_find_free_minor();
#else
	minor = snd_kernel_minor(type, card, dev);
	if (minor >= 0 && snd_minors[minor])
		minor = -EBUSY;
#endif
	if (minor < 0) {
		mutex_unlock(&sound_mutex);
		kfree(preg);
		return minor;
	}
	snd_minors[minor] = preg;
	preg->dev = device_create(sound_class, device, MKDEV(major, minor),
				  private_data, "%s", name);
	if (IS_ERR(preg->dev)) {
		snd_minors[minor] = NULL;
		mutex_unlock(&sound_mutex);
		minor = PTR_ERR(preg->dev);
		kfree(preg);
		return minor;
	}

	mutex_unlock(&sound_mutex);
	return 0;
}