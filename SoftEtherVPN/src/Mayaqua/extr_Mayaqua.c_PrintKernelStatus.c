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
 int /*<<< orphan*/  GetLine (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IsHamMode () ; 
 int /*<<< orphan*/  KS_CURRENT_LOCKED_COUNT ; 
 int /*<<< orphan*/  KS_CURRENT_LOCK_COUNT ; 
 int /*<<< orphan*/  KS_CURRENT_MEM_COUNT ; 
 int /*<<< orphan*/  KS_CURRENT_REFED_COUNT ; 
 int /*<<< orphan*/  KS_CURRENT_REF_COUNT ; 
 int /*<<< orphan*/  KS_DELETELOCK_COUNT ; 
 int /*<<< orphan*/  KS_FREEREF_COUNT ; 
 int /*<<< orphan*/  KS_FREETHREAD_COUNT ; 
 int /*<<< orphan*/  KS_FREE_COUNT ; 
 scalar_t__ KS_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_GET64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_GETMAX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_GETTICK_COUNT ; 
 int /*<<< orphan*/  KS_GETTIME_COUNT ; 
 int /*<<< orphan*/  KS_MALLOC_COUNT ; 
 int /*<<< orphan*/  KS_MEMPOOL_CURRENT_NUM ; 
 int /*<<< orphan*/  KS_MEMPOOL_MALLOC_COUNT ; 
 int /*<<< orphan*/  KS_MEMPOOL_REALLOC_COUNT ; 
 int /*<<< orphan*/  KS_NEWLOCK_COUNT ; 
 int /*<<< orphan*/  KS_NEWREF_COUNT ; 
 int /*<<< orphan*/  KS_NEWTHREAD_COUNT ; 
 int /*<<< orphan*/  KS_REALLOC_COUNT ; 
 int /*<<< orphan*/  KS_TOTAL_MEM_COUNT ; 
 int /*<<< orphan*/  KS_TOTAL_MEM_SIZE ; 
 int /*<<< orphan*/  KS_WAIT_COUNT ; 
 int /*<<< orphan*/  Print (char*,...) ; 
 int g_memcheck ; 

void PrintKernelStatus()
{
	bool leaked = false;

	Print("\n");
	Print(
		"     --------- Mayaqua Kernel Status ---------\n"
		"        Malloc Count ............... %u\n"
		"        ReAlloc Count .............. %u\n"
		"        Free Count ................. %u\n"
		"        Total Memory Size .......... %I64u bytes\n"
		"      * Current Memory Blocks ...... %u Blocks (Peek: %u)\n"
		"        Total Memory Blocks ........ %u Blocks\n"
		"      * Current MemPool Blocks ..... %u Blocks (Peek: %u)\n"
		"        Total MemPool Mallocs ...... %u Mallocs\n"
		"        Total MemPool ReAllocs ..... %u ReAllocs\n"
		"        NewLock Count .............. %u\n"
		"        DeleteLock Count ........... %u\n"
		"      * Current Lock Objects ....... %u Objects\n"
		"      * Current Locked Objects ..... %u Objects\n"
		"        NewRef Count ............... %u\n"
		"        FreeRef Count .............. %u\n"
		"      * Current Ref Objects ........ %u Objects\n"
		"      * Current Ref Count .......... %u Refs\n"
		"        GetTime Count .............. %u\n"
		"        GetTick Count .............. %u\n"
		"        NewThread Count ............ %u\n"
		"        FreeThread Count ........... %u\n"
		"      * Current Threads ............ %u Threads\n"
		"        Wait For Event Count ....... %u\n\n",
		KS_GET(KS_MALLOC_COUNT),
		KS_GET(KS_REALLOC_COUNT),
		KS_GET(KS_FREE_COUNT),
		KS_GET64(KS_TOTAL_MEM_SIZE),
		KS_GET(KS_CURRENT_MEM_COUNT),
		KS_GETMAX(KS_CURRENT_MEM_COUNT),
		KS_GET(KS_TOTAL_MEM_COUNT),
		KS_GET(KS_MEMPOOL_CURRENT_NUM),
		KS_GETMAX(KS_MEMPOOL_CURRENT_NUM),
		KS_GET(KS_MEMPOOL_MALLOC_COUNT),
		KS_GET(KS_MEMPOOL_REALLOC_COUNT),
		KS_GET(KS_NEWLOCK_COUNT),
		KS_GET(KS_DELETELOCK_COUNT),
		KS_GET(KS_CURRENT_LOCK_COUNT),
		KS_GET(KS_CURRENT_LOCKED_COUNT),
		KS_GET(KS_NEWREF_COUNT),
		KS_GET(KS_FREEREF_COUNT),
		KS_GET(KS_CURRENT_REF_COUNT),
		KS_GET(KS_CURRENT_REFED_COUNT),
		KS_GET(KS_GETTIME_COUNT),
		KS_GET(KS_GETTICK_COUNT),
		KS_GET(KS_NEWTHREAD_COUNT),
		KS_GET(KS_FREETHREAD_COUNT),
		KS_GET(KS_NEWTHREAD_COUNT) - KS_GET(KS_FREETHREAD_COUNT),
		KS_GET(KS_WAIT_COUNT)
		);

	if (KS_GET(KS_CURRENT_MEM_COUNT) != 0 || KS_GET(KS_CURRENT_LOCK_COUNT) != 0 ||
		KS_GET(KS_MEMPOOL_CURRENT_NUM) != 0 ||
		KS_GET(KS_CURRENT_LOCKED_COUNT) != 0 || KS_GET(KS_CURRENT_REF_COUNT) != 0)
	{
		leaked = true;
	}

	if (leaked)
	{
		Print("      !!! MEMORY LEAKS DETECTED !!!\n\n");
		if (g_memcheck == false)
		{
			if (IsHamMode())
			{
				Print("    Enable /memcheck startup option to see the leaking memory heap.\n");
				Print("    Press Enter key to exit the process.\n");
			}
			GetLine(NULL, 0);
		}
	}
	else
	{
		Print("        @@@ NO MEMORY LEAKS @@@\n\n");
	}
}