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

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 uintptr_t hash_mix (uintptr_t) ; 

uint32_t
hashbacktrace(uintptr_t* bt, uint32_t depth, uint32_t max_size)
{

	uintptr_t hash = 0;
	uintptr_t mask = max_size - 1;

	while (depth) {
		hash += bt[--depth];
	}

	hash = hash_mix(hash) & mask;

	assert(hash < max_size);

	return (uint32_t) hash;
}