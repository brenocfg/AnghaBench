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

__attribute__((used)) static inline unsigned
gf256red(unsigned x)
{
	unsigned y;

	y = x >> 8;
	return (x ^ y ^ (y << 1) ^ (y << 3) ^ (y << 4)) & 0xFF;
}