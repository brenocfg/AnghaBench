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
typedef  int uint32_t ;
struct dm_target {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_power_of_2 (int) ; 

__attribute__((used)) static int _check_region_size(struct dm_target *ti, uint32_t region_size)
{
	if (region_size < 2 || region_size > ti->len)
		return 0;

	if (!is_power_of_2(region_size))
		return 0;

	return 1;
}