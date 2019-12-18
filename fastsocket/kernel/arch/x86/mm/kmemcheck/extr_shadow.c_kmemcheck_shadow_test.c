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
typedef  scalar_t__ uint8_t ;
typedef  enum kmemcheck_shadow { ____Placeholder_kmemcheck_shadow } kmemcheck_shadow ;

/* Variables and functions */
 scalar_t__ KMEMCHECK_SHADOW_INITIALIZED ; 

enum kmemcheck_shadow kmemcheck_shadow_test(void *shadow, unsigned int size)
{
	uint8_t *x;
	unsigned int i;

	x = shadow;

#ifdef CONFIG_KMEMCHECK_PARTIAL_OK
	/*
	 * Make sure _some_ bytes are initialized. Gcc frequently generates
	 * code to access neighboring bytes.
	 */
	for (i = 0; i < size; ++i) {
		if (x[i] == KMEMCHECK_SHADOW_INITIALIZED)
			return x[i];
	}
#else
	/* All bytes must be initialized. */
	for (i = 0; i < size; ++i) {
		if (x[i] != KMEMCHECK_SHADOW_INITIALIZED)
			return x[i];
	}
#endif

	return x[0];
}