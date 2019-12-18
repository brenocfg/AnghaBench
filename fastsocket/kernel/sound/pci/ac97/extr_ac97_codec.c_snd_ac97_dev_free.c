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
struct snd_device {struct snd_ac97* device_data; } ;
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int snd_ac97_free (struct snd_ac97*) ; 
 int /*<<< orphan*/  snd_ac97_powerdown (struct snd_ac97*) ; 

__attribute__((used)) static int snd_ac97_dev_free(struct snd_device *device)
{
	struct snd_ac97 *ac97 = device->device_data;
	snd_ac97_powerdown(ac97); /* for avoiding click noises during shut down */
	return snd_ac97_free(ac97);
}