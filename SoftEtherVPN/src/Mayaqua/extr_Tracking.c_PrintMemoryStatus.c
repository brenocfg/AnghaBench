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
struct TYPE_3__ {int /*<<< orphan*/  MemorySize; int /*<<< orphan*/  MemoryBlocksNum; } ;
typedef  TYPE_1__ MEMORY_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  GetMemoryStatus (TYPE_1__*) ; 
 int /*<<< orphan*/  Print (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void PrintMemoryStatus()
{
	MEMORY_STATUS s;
	GetMemoryStatus(&s);
	Print("MEMORY STATUS:\n"
		" NUM_OF_MEMORY_BLOCKS: %u\n"
		" SIZE_OF_TOTAL_MEMORY: %u bytes\n",
		s.MemoryBlocksNum, s.MemorySize);
}