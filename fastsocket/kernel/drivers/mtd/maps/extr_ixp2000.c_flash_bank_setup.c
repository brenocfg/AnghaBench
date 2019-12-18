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
struct map_info {scalar_t__ map_priv_2; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long flash_bank_setup(struct map_info *map, unsigned long ofs)
{
	unsigned long (*set_bank)(unsigned long) =
		(unsigned long(*)(unsigned long))map->map_priv_2;

	return (set_bank ? set_bank(ofs) : ofs);
}