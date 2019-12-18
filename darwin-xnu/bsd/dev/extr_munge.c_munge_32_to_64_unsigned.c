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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline __attribute__((always_inline)) void 
munge_32_to_64_unsigned(volatile uint64_t *dest, volatile uint32_t *src, int count)
{
	int i;

	for (i = count - 1; i >= 0; i--) {
		dest[i] = src[i];
	}   
}