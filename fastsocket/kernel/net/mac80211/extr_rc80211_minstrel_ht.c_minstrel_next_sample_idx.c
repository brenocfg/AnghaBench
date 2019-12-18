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
struct minstrel_mcs_group_data {scalar_t__ index; size_t column; int /*<<< orphan*/  supported; } ;
struct minstrel_ht_sta {size_t sample_group; struct minstrel_mcs_group_data* groups; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ MCS_GROUP_RATES ; 
 int /*<<< orphan*/  minstrel_mcs_groups ; 
 int /*<<< orphan*/  sample_table ; 

__attribute__((used)) static void
minstrel_next_sample_idx(struct minstrel_ht_sta *mi)
{
	struct minstrel_mcs_group_data *mg;

	for (;;) {
		mi->sample_group++;
		mi->sample_group %= ARRAY_SIZE(minstrel_mcs_groups);
		mg = &mi->groups[mi->sample_group];

		if (!mg->supported)
			continue;

		if (++mg->index >= MCS_GROUP_RATES) {
			mg->index = 0;
			if (++mg->column >= ARRAY_SIZE(sample_table))
				mg->column = 0;
		}
		break;
	}
}