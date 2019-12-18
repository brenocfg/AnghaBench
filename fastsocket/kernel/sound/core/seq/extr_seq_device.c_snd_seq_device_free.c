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
struct snd_seq_device {int /*<<< orphan*/  (* private_free ) (struct snd_seq_device*) ;int /*<<< orphan*/  list; int /*<<< orphan*/  id; } ;
struct ops_list {int /*<<< orphan*/  reg_mutex; int /*<<< orphan*/  num_devices; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 struct ops_list* find_driver (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_device (struct snd_seq_device*,struct ops_list*) ; 
 int /*<<< orphan*/  kfree (struct snd_seq_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct snd_seq_device*) ; 
 int /*<<< orphan*/  unlock_driver (struct ops_list*) ; 

__attribute__((used)) static int snd_seq_device_free(struct snd_seq_device *dev)
{
	struct ops_list *ops;

	if (snd_BUG_ON(!dev))
		return -EINVAL;

	ops = find_driver(dev->id, 0);
	if (ops == NULL)
		return -ENXIO;

	/* remove the device from the list */
	mutex_lock(&ops->reg_mutex);
	list_del(&dev->list);
	ops->num_devices--;
	mutex_unlock(&ops->reg_mutex);

	free_device(dev, ops);
	if (dev->private_free)
		dev->private_free(dev);
	kfree(dev);

	unlock_driver(ops);

	return 0;
}