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
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void pod_resolve(const char *buf, short block0, short block1, unsigned char *location)
{
	int value = simple_strtoul(buf, NULL, 10);
	short block = (value < 0x40) ? block0 : block1;
	value &= 0x3f;
	location[0] = block >> 7;
	location[1] = value | (block & 0x7f);
}