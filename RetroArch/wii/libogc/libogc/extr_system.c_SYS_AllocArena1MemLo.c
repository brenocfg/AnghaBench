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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ SYS_GetArena1Lo () ; 
 int /*<<< orphan*/  SYS_SetArena1Lo (void*) ; 

void* SYS_AllocArena1MemLo(u32 size,u32 align)
{
	u32 mem1lo;
	void *ptr = NULL;

	mem1lo = (u32)SYS_GetArena1Lo();
	ptr = (void*)((mem1lo+(align-1))&~(align-1));
	mem1lo = ((((u32)ptr+size+align)-1)&~(align-1));
	SYS_SetArena1Lo((void*)mem1lo);

	return ptr;
}