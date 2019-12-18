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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  used_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lwp_heap_getinfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  __wkspace_heap ; 
 TYPE_1__ __wkspace_iblock ; 

u32 __lwp_wkspace_heapused()
{
	__lwp_heap_getinfo(&__wkspace_heap,&__wkspace_iblock);
	return __wkspace_iblock.used_size;
}