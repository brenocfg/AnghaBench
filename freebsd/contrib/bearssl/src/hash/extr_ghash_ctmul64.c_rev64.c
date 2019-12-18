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
 int /*<<< orphan*/  RMS (int,int) ; 

__attribute__((used)) static uint64_t
rev64(uint64_t x)
{
#define RMS(m, s)   do { \
		x = ((x & (uint64_t)(m)) << (s)) \
			| ((x >> (s)) & (uint64_t)(m)); \
	} while (0)

	RMS(0x5555555555555555,  1);
	RMS(0x3333333333333333,  2);
	RMS(0x0F0F0F0F0F0F0F0F,  4);
	RMS(0x00FF00FF00FF00FF,  8);
	RMS(0x0000FFFF0000FFFF, 16);
	return (x << 32) | (x >> 32);

#undef RMS
}