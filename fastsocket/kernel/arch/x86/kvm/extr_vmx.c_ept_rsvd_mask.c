#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
struct TYPE_2__ {int x86_phys_bits; } ;

/* Variables and functions */
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static u64 ept_rsvd_mask(u64 spte, int level)
{
	int i;
	u64 mask = 0;

	for (i = 51; i > boot_cpu_data.x86_phys_bits; i--)
		mask |= (1ULL << i);

	if (level > 2)
		/* bits 7:3 reserved */
		mask |= 0xf8;
	else if (level == 2) {
		if (spte & (1ULL << 7))
			/* 2MB ref, bits 20:12 reserved */
			mask |= 0x1ff000;
		else
			/* bits 6:3 reserved */
			mask |= 0x78;
	}

	return mask;
}