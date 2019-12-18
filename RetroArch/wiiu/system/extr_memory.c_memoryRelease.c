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

/* Variables and functions */
 int /*<<< orphan*/  MEMDestroyExpHeap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEMFreeToFrmHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMGetBaseHeapHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_BASE_HEAP_FG ; 
 int /*<<< orphan*/  MEM_BASE_HEAP_MEM1 ; 
 int /*<<< orphan*/  MEM_FRAME_HEAP_FREE_ALL ; 
 int /*<<< orphan*/ * bucket_heap ; 
 int /*<<< orphan*/ * mem1_heap ; 

void memoryRelease(void)
{
    MEMDestroyExpHeap(mem1_heap);
    MEMFreeToFrmHeap(MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM1), MEM_FRAME_HEAP_FREE_ALL);
    mem1_heap = NULL;

    MEMDestroyExpHeap(bucket_heap);
    MEMFreeToFrmHeap(MEMGetBaseHeapHandle(MEM_BASE_HEAP_FG), MEM_FRAME_HEAP_FREE_ALL);
    bucket_heap = NULL;
}