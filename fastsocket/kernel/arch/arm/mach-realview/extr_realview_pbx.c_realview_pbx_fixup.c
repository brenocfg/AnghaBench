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
struct tag {int dummy; } ;
struct meminfo {int nr_banks; TYPE_1__* bank; } ;
struct machine_desc {int dummy; } ;
struct TYPE_2__ {int start; void* size; } ;

/* Variables and functions */
 void* SZ_256M ; 
 void* SZ_512M ; 
 int /*<<< orphan*/  realview_fixup (struct machine_desc*,struct tag*,char**,struct meminfo*) ; 

__attribute__((used)) static void realview_pbx_fixup(struct machine_desc *mdesc, struct tag *tags,
			       char **from, struct meminfo *meminfo)
{
#ifdef CONFIG_SPARSEMEM
	/*
	 * Memory configuration with SPARSEMEM enabled on RealView PBX (see
	 * asm/mach/memory.h for more information).
	 */
	meminfo->bank[0].start = 0;
	meminfo->bank[0].size = SZ_256M;
	meminfo->bank[1].start = 0x20000000;
	meminfo->bank[1].size = SZ_512M;
	meminfo->bank[2].start = 0x80000000;
	meminfo->bank[2].size = SZ_256M;
	meminfo->nr_banks = 3;
#else
	realview_fixup(mdesc, tags, from, meminfo);
#endif
}