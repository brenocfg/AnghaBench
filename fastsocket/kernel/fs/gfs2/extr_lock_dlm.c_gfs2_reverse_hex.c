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
 int /*<<< orphan*/ * hex_asc ; 

__attribute__((used)) static void gfs2_reverse_hex(char *c, u64 value)
{
	*c = '0';
	while (value) {
		*c-- = hex_asc[value & 0x0f];
		value >>= 4;
	}
}