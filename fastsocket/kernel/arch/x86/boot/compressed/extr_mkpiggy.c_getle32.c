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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t getle32(const void *p)
{
	const uint8_t *cp = p;

	return (uint32_t)cp[0] + ((uint32_t)cp[1] << 8) +
		((uint32_t)cp[2] << 16) + ((uint32_t)cp[3] << 24);
}