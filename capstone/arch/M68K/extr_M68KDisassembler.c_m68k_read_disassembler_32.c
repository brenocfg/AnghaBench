#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int* code; } ;
typedef  TYPE_1__ m68k_info ;

/* Variables and functions */

__attribute__((used)) static unsigned int m68k_read_disassembler_32(const m68k_info *info, const uint64_t addr)
{
	const uint32_t v0 = info->code[addr + 0];
	const uint32_t v1 = info->code[addr + 1];
	const uint32_t v2 = info->code[addr + 2];
	const uint32_t v3 = info->code[addr + 3];
	return (v0 << 24) | (v1 << 16) | (v2 << 8) | v3;
}