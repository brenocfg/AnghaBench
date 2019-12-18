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
typedef  int uint16_t ;

/* Variables and functions */

uint16_t
nat464_cksum_fixup(uint16_t cksum, uint16_t old, uint16_t new, uint8_t udp)
{
	uint32_t l;

	if (udp && !cksum)
		return (0);
	l = cksum + old - new;
	l = (l >> 16) + (l & 0xffff);
	l = l & 0xffff;
	if (udp && !l)
		return (0xffff);
	return (l);
}