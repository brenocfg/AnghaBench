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
struct TYPE_3__ {int* code; } ;
typedef  TYPE_1__ m68k_info ;

/* Variables and functions */

__attribute__((used)) static uint64_t m68k_read_disassembler_64(const m68k_info *info, const uint64_t addr)
{
	const uint64_t v0 = info->code[addr + 0];
	const uint64_t v1 = info->code[addr + 1];
	const uint64_t v2 = info->code[addr + 2];
	const uint64_t v3 = info->code[addr + 3];
	const uint64_t v4 = info->code[addr + 4];
	const uint64_t v5 = info->code[addr + 5];
	const uint64_t v6 = info->code[addr + 6];
	const uint64_t v7 = info->code[addr + 7];
	return (v0 << 56) | (v1 << 48) | (v2 << 40) | (v3 << 32) | (v4 << 24) | (v5 << 16) | (v6 << 8) | v7;
}