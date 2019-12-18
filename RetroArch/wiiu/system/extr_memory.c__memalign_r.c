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
struct _reent {int dummy; } ;

/* Variables and functions */
 void* MEMAllocFromExpHeapEx (int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  MEMGetBaseHeapHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_BASE_HEAP_MEM2 ; 

void* _memalign_r(struct _reent *r, size_t alignment, size_t size)
{
   return MEMAllocFromExpHeapEx(MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM2), size, alignment);
}