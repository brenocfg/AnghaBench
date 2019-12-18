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
struct TYPE_2__ {int index; int /*<<< orphan*/  name; } ;
struct snd_kcontrol {scalar_t__ private_value; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  jack_detect_kctl ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 

struct snd_kcontrol *
snd_kctl_jack_new(const char *name, int idx, void *private_data)
{
	struct snd_kcontrol *kctl;
	kctl = snd_ctl_new1(&jack_detect_kctl, private_data);
	if (!kctl)
		return NULL;
	snprintf(kctl->id.name, sizeof(kctl->id.name), "%s Jack", name);
	kctl->id.index = idx;
	kctl->private_value = 0;
	return kctl;
}