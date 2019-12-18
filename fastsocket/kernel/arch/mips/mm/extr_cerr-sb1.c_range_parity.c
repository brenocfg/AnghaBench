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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static char range_parity(uint64_t dword, int max, int min)
{
	char parity = 0;
	int i;
	dword >>= min;
	for (i=max-min; i>=0; i--) {
		if (dword & 0x1)
			parity = !parity;
		dword >>= 1;
	}
	return parity;
}