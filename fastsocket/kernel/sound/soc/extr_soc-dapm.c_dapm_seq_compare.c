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
struct snd_soc_dapm_widget {size_t id; scalar_t__ reg; } ;

/* Variables and functions */

__attribute__((used)) static int dapm_seq_compare(struct snd_soc_dapm_widget *a,
			    struct snd_soc_dapm_widget *b,
			    int sort[])
{
	if (sort[a->id] != sort[b->id])
		return sort[a->id] - sort[b->id];
	if (a->reg != b->reg)
		return a->reg - b->reg;

	return 0;
}