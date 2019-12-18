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
 int DYNAMIC_DEBUG_HASH_BITS ; 

__attribute__((used)) static unsigned int djb2_hash(char *str)
{
	unsigned long hash = 5381;
	int c;

	c = *str;
	while (c) {
		hash = ((hash << 5) + hash) + c;
		c = *++str;
	}
	return (unsigned int)(hash & ((1 << DYNAMIC_DEBUG_HASH_BITS) - 1));
}