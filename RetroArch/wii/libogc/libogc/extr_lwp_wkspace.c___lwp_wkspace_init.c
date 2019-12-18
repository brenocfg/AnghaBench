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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PPC_ALIGNMENT ; 
 scalar_t__ ROUND32UP (scalar_t__) ; 
 scalar_t__ SYS_GetArenaLo () ; 
 int /*<<< orphan*/  SYS_SetArenaLo (void*) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (scalar_t__) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (scalar_t__) ; 
 scalar_t__ __lwp_heap_init (int /*<<< orphan*/ *,void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wkspace_heap ; 
 int /*<<< orphan*/  __wkspace_heap_size ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 

void __lwp_wkspace_init(u32 size)
{
	u32 arLo,level,dsize;

	// Get current ArenaLo and adjust to 32-byte boundary
	_CPU_ISR_Disable(level);
	arLo = ROUND32UP(SYS_GetArenaLo());
	dsize = (size - (arLo - (u32)SYS_GetArenaLo()));
	SYS_SetArenaLo((void*)(arLo+dsize));
	_CPU_ISR_Restore(level);

	memset((void*)arLo,0,dsize);
	__wkspace_heap_size += __lwp_heap_init(&__wkspace_heap,(void*)arLo,dsize,PPC_ALIGNMENT);
}