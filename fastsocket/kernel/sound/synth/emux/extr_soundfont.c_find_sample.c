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
struct snd_soundfont {struct snd_sf_sample* samples; } ;
struct TYPE_2__ {int sample; } ;
struct snd_sf_sample {TYPE_1__ v; struct snd_sf_sample* next; } ;

/* Variables and functions */

__attribute__((used)) static struct snd_sf_sample *
find_sample(struct snd_soundfont *sf, int sample_id)
{
	struct snd_sf_sample *p;

	if (sf == NULL)
		return NULL;

	for (p = sf->samples; p; p = p->next) {
		if (p->v.sample == sample_id)
			return p;
	}
	return NULL;
}