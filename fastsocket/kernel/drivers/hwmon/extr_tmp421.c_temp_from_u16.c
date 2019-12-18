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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static int temp_from_u16(u16 reg)
{
	/* Mask out status bits */
	int temp = reg & ~0xf;

	/* Add offset for extended temperature range. */
	temp -= 64 * 256;

	return (temp * 1000 + 128) / 256;
}