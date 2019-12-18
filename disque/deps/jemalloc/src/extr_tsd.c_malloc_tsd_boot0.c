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

/* Variables and functions */
 scalar_t__ ncleanups ; 
 int* tsd_arenas_cache_bypassp_get (int /*<<< orphan*/ ) ; 
 scalar_t__ tsd_boot0 () ; 
 int /*<<< orphan*/  tsd_fetch () ; 

bool
malloc_tsd_boot0(void)
{

	ncleanups = 0;
	if (tsd_boot0())
		return (true);
	*tsd_arenas_cache_bypassp_get(tsd_fetch()) = true;
	return (false);
}