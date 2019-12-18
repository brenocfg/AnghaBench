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
 size_t s2u (size_t) ; 

__attribute__((used)) static size_t
zone_good_size(malloc_zone_t *zone, size_t size)
{

	if (size == 0)
		size = 1;
	return (s2u(size));
}