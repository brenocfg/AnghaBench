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
typedef  unsigned int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t zi_read32(const unsigned char *z)
{
	return (unsigned)z[0]<<24 | z[1]<<16 | z[2]<<8 | z[3];
}