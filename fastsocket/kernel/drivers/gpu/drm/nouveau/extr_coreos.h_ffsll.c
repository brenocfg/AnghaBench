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
typedef  unsigned long long u64 ;

/* Variables and functions */

__attribute__((used)) static inline int
ffsll(u64 mask)
{
	int i;
	for (i = 0; i < 64; i++) {
		if (mask & (1ULL << i))
			return i + 1;
	}
	return 0;
}