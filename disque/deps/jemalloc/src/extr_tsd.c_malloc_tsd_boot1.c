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
 int* tsd_arenas_cache_bypassp_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_boot1 () ; 
 int /*<<< orphan*/  tsd_fetch () ; 

void
malloc_tsd_boot1(void)
{

	tsd_boot1();
	*tsd_arenas_cache_bypassp_get(tsd_fetch()) = false;
}