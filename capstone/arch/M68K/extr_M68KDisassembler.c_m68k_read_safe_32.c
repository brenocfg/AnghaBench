#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ const baseAddress; scalar_t__ const address_mask; scalar_t__ const code_len; } ;
typedef  TYPE_1__ m68k_info ;

/* Variables and functions */
 unsigned int m68k_read_disassembler_32 (TYPE_1__ const*,scalar_t__ const) ; 

__attribute__((used)) static unsigned int m68k_read_safe_32(const m68k_info *info, const uint64_t address)
{
	const uint64_t addr = (address - info->baseAddress) & info->address_mask;
	if (info->code_len < addr + 4) {
		return 0xaaaaaaaa;
	}
	return m68k_read_disassembler_32(info, addr);
}