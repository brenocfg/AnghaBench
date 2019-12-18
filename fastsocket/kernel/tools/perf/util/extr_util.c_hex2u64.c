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
typedef  int u64 ;

/* Variables and functions */
 int hex (char const) ; 

int hex2u64(const char *ptr, u64 *long_val)
{
	const char *p = ptr;
	*long_val = 0;

	while (*p) {
		const int hex_val = hex(*p);

		if (hex_val < 0)
			break;

		*long_val = (*long_val << 4) | hex_val;
		p++;
	}

	return p - ptr;
}