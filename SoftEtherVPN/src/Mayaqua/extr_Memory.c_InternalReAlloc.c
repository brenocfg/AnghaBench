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
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  AbortExitEx (char*) ; 
 int /*<<< orphan*/  KS_ADD (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_REALLOC_COUNT ; 
 int /*<<< orphan*/  KS_TOTAL_MEM_SIZE ; 
 scalar_t__ MEMORY_MAX_RETRY ; 
 int /*<<< orphan*/  MEMORY_SLEEP_TIME ; 
 scalar_t__ MORE (scalar_t__,int) ; 
 void* OSMemoryReAlloc (void*,scalar_t__) ; 
 int /*<<< orphan*/  OSSleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POINTER_TO_UINT64 (void*) ; 
 int /*<<< orphan*/  TrackChangeObjSize (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void *InternalReAlloc(void *addr, UINT size)
{
	void *new_addr;
	UINT retry = 0;
	size = MORE(size, 1);

	// KS
	KS_INC(KS_REALLOC_COUNT);
	KS_ADD(KS_TOTAL_MEM_SIZE, size);

	// Attempt to allocate memory until success
	while (true)
	{
		if ((retry++) > MEMORY_MAX_RETRY)
		{
			AbortExitEx("InternalReAlloc: error: realloc() failed.\n\n");
		}
		new_addr = OSMemoryReAlloc(addr, size);
		if (new_addr != NULL)
		{
			break;
		}

		OSSleep(MEMORY_SLEEP_TIME);
	}

	TrackChangeObjSize(POINTER_TO_UINT64(addr), size, POINTER_TO_UINT64(new_addr));

	return new_addr;
}