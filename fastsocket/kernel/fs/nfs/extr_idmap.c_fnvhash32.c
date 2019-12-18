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
 unsigned int FNV_1_32 ; 
 unsigned int FNV_P_32 ; 

__attribute__((used)) static unsigned int fnvhash32(const void *buf, size_t buflen)
{
	const unsigned char *p, *end = (const unsigned char *)buf + buflen;
	unsigned int hash = FNV_1_32;

	for (p = buf; p < end; p++) {
		hash *= FNV_P_32;
		hash ^= (unsigned int)*p;
	}

	return hash;
}