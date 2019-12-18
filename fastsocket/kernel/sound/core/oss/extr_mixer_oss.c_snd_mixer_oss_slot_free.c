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
struct snd_mixer_oss_slot {scalar_t__ private_data; } ;
struct slot {struct slot* assigned; struct slot* name; scalar_t__ allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct slot*) ; 

__attribute__((used)) static void snd_mixer_oss_slot_free(struct snd_mixer_oss_slot *chn)
{
	struct slot *p = (struct slot *)chn->private_data;
	if (p) {
		if (p->allocated && p->assigned) {
			kfree(p->assigned->name);
			kfree(p->assigned);
		}
		kfree(p);
	}
}