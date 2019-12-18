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
struct snd_mixer_oss_slot {int number; int /*<<< orphan*/  (* private_free ) (struct snd_mixer_oss_slot*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct snd_mixer_oss_slot*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct snd_mixer_oss_slot*) ; 

__attribute__((used)) static void mixer_slot_clear(struct snd_mixer_oss_slot *rslot)
{
	int idx = rslot->number; /* remember this */
	if (rslot->private_free)
		rslot->private_free(rslot);
	memset(rslot, 0, sizeof(*rslot));
	rslot->number = idx;
}