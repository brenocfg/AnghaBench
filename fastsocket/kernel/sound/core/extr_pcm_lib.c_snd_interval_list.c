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
struct snd_interval {int empty; scalar_t__ max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UINT_MAX ; 
 scalar_t__ max (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_interval_any (struct snd_interval*) ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval*) ; 
 int /*<<< orphan*/  snd_interval_test (struct snd_interval*,unsigned int) ; 

int snd_interval_list(struct snd_interval *i, unsigned int count, unsigned int *list, unsigned int mask)
{
        unsigned int k;
	struct snd_interval list_range;

	if (!count) {
		i->empty = 1;
		return -EINVAL;
	}
	snd_interval_any(&list_range);
	list_range.min = UINT_MAX;
	list_range.max = 0;
        for (k = 0; k < count; k++) {
		if (mask && !(mask & (1 << k)))
			continue;
		if (!snd_interval_test(i, list[k]))
			continue;
		list_range.min = min(list_range.min, list[k]);
		list_range.max = max(list_range.max, list[k]);
        }
	return snd_interval_refine(i, &list_range);
}