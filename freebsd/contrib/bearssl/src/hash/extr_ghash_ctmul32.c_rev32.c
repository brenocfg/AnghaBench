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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  RMS (int,int) ; 

__attribute__((used)) static uint32_t
rev32(uint32_t x)
{
#define RMS(m, s)   do { \
		x = ((x & (uint32_t)(m)) << (s)) \
			| ((x >> (s)) & (uint32_t)(m)); \
	} while (0)

	RMS(0x55555555, 1);
	RMS(0x33333333, 2);
	RMS(0x0F0F0F0F, 4);
	RMS(0x00FF00FF, 8);
	return (x << 16) | (x >> 16);

#undef RMS
}