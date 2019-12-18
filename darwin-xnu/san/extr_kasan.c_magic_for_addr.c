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
typedef  int vm_offset_t ;
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t
magic_for_addr(vm_offset_t addr, uint16_t magic_xor)
{
	uint16_t magic = addr & 0xFFFF;
	magic ^= (addr >> 16) & 0xFFFF;
	magic ^= (addr >> 32) & 0xFFFF;
	magic ^= (addr >> 48) & 0xFFFF;
	magic ^= magic_xor;
	return magic;
}