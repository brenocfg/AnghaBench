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
 int /*<<< orphan*/  KS_CURRENT_MEM_COUNT ; 
 int /*<<< orphan*/  KS_DEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_FREE_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSMemoryFree (void*) ; 
 int /*<<< orphan*/  POINTER_TO_UINT64 (void*) ; 
 int /*<<< orphan*/  TrackDeleteObj (int /*<<< orphan*/ ) ; 

void InternalFree(void *addr)
{
	// Validate arguments
	if (addr == NULL)
	{
		return;
	}

	// KS
	KS_DEC(KS_CURRENT_MEM_COUNT);
	KS_INC(KS_FREE_COUNT);

	TrackDeleteObj(POINTER_TO_UINT64(addr));

	// Memory release
	OSMemoryFree(addr);
}