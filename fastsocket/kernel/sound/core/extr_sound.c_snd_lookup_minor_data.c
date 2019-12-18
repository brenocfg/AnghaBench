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
struct snd_minor {int type; void* private_data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct snd_minor**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_minor** snd_minors ; 
 int /*<<< orphan*/  sound_mutex ; 

void *snd_lookup_minor_data(unsigned int minor, int type)
{
	struct snd_minor *mreg;
	void *private_data;

	if (minor >= ARRAY_SIZE(snd_minors))
		return NULL;
	mutex_lock(&sound_mutex);
	mreg = snd_minors[minor];
	if (mreg && mreg->type == type)
		private_data = mreg->private_data;
	else
		private_data = NULL;
	mutex_unlock(&sound_mutex);
	return private_data;
}