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
 unsigned int FNV_OFFSET ; 
 unsigned int FNV_PRIME ; 

unsigned int
libelftc_hash_string(const char *s)
{
	char c;
	unsigned int hash;

	for (hash = FNV_OFFSET; (c = *s) != '\0'; s++) {
		hash ^= c;
		hash *= FNV_PRIME;
	}

	return (hash);
}