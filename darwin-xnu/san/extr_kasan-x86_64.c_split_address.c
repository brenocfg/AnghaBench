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
typedef  int vm_offset_t ;
struct TYPE_3__ {int pml4; int pdpt; int pd; int pt; } ;
typedef  TYPE_1__ split_addr_t ;

/* Variables and functions */

__attribute__((used)) static split_addr_t
split_address(vm_offset_t address)
{
	split_addr_t addr;

	addr.pml4   = (address >> 39) & 0x1ff;
	addr.pdpt   = (address >> 30) & 0x1ff;
	addr.pd     = (address >> 21) & 0x1ff;
	addr.pt     = (address >> 12) & 0x1ff;
	// addr.offset = address & PAGE_MASK;

	return addr;
}