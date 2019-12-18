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
struct snd_timer {int /*<<< orphan*/  device_list; } ;
struct snd_device {struct snd_timer* device_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_mutex ; 

__attribute__((used)) static int snd_timer_dev_disconnect(struct snd_device *device)
{
	struct snd_timer *timer = device->device_data;
	mutex_lock(&register_mutex);
	list_del_init(&timer->device_list);
	mutex_unlock(&register_mutex);
	return 0;
}