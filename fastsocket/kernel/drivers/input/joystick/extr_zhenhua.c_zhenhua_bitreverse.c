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

__attribute__((used)) static int zhenhua_bitreverse(int x)
{
	x = ((x & 0xaa) >> 1) | ((x & 0x55) << 1);
	x = ((x & 0xcc) >> 2) | ((x & 0x33) << 2);
	x = ((x & 0xf0) >> 4) | ((x & 0x0f) << 4);
	return x;
}