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
typedef  int uint16_t ;
struct TYPE_3__ {int* code; } ;
typedef  TYPE_1__ m68k_info ;

/* Variables and functions */

__attribute__((used)) static unsigned int m68k_read_disassembler_16(const m68k_info *info, const uint64_t addr)
{
	const uint16_t v0 = info->code[addr + 0];
	const uint16_t v1 = info->code[addr + 1];
	return (v0 << 8) | v1;
}