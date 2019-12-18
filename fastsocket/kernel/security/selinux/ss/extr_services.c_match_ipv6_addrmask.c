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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static int match_ipv6_addrmask(u32 *input, u32 *addr, u32 *mask)
{
	int i, fail = 0;

	for (i = 0; i < 4; i++)
		if (addr[i] != (input[i] & mask[i])) {
			fail = 1;
			break;
		}

	return !fail;
}