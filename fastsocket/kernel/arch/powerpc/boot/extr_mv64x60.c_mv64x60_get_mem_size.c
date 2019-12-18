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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 int MV64x60_CPU2MEM_WINDOWS ; 
 int MV64x60_CPU_BAR_ENABLE ; 
 int in_le32 (int*) ; 
 TYPE_1__* mv64x60_cpu2mem ; 

u32 mv64x60_get_mem_size(u8 *bridge_base)
{
	u32 enables, i, v;
	u32 mem = 0;

	enables = in_le32((u32 *)(bridge_base + MV64x60_CPU_BAR_ENABLE)) & 0xf;

	for (i=0; i<MV64x60_CPU2MEM_WINDOWS; i++)
		if (!(enables & (1<<i))) {
			v = in_le32((u32*)(bridge_base
						+ mv64x60_cpu2mem[i].size));
			v = ((v & 0xffff) + 1) << 16;
			mem += v;
		}

	return mem;
}