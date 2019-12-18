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
typedef  int /*<<< orphan*/  malloc_zone_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_prof ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ ivsalloc (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  je_free (void*) ; 

__attribute__((used)) static void
zone_free(malloc_zone_t *zone, void *ptr)
{

	if (ivsalloc(ptr, config_prof) != 0) {
		je_free(ptr);
		return;
	}

	free(ptr);
}