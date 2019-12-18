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
struct stripe_chunk {int dummy; } ;
struct stripe {int dummy; } ;
struct TYPE_2__ {int raid_devs; } ;
struct raid_set {TYPE_1__ set; } ;

/* Variables and functions */

__attribute__((used)) static size_t stripe_size(struct raid_set *rs)
{
	return sizeof(struct stripe) +
		      rs->set.raid_devs * sizeof(struct stripe_chunk);
}