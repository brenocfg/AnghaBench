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
struct snd_seq_device {int /*<<< orphan*/  id; } ;
struct snd_device {struct snd_seq_device* device_data; } ;
struct ops_list {int driver; } ;

/* Variables and functions */
 int DRIVER_LOADED ; 
 int ENOENT ; 
 struct ops_list* find_driver (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_device (struct snd_seq_device*,struct ops_list*) ; 
 int /*<<< orphan*/  unlock_driver (struct ops_list*) ; 

__attribute__((used)) static int snd_seq_device_dev_register(struct snd_device *device)
{
	struct snd_seq_device *dev = device->device_data;
	struct ops_list *ops;

	ops = find_driver(dev->id, 0);
	if (ops == NULL)
		return -ENOENT;

	/* initialize this device if the corresponding driver was
	 * already loaded
	 */
	if (ops->driver & DRIVER_LOADED)
		init_device(dev, ops);

	unlock_driver(ops);
	return 0;
}