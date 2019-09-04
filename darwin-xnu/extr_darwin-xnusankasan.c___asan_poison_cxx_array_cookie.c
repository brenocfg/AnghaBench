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
typedef  int /*<<< orphan*/  uptr ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASAN_ARRAY_COOKIE ; 
 int /*<<< orphan*/ * SHADOW_FOR_ADDRESS (int /*<<< orphan*/ ) ; 

void
__asan_poison_cxx_array_cookie(uptr p)
{
	uint8_t *shadow = SHADOW_FOR_ADDRESS(p);
	*shadow = ASAN_ARRAY_COOKIE;
}