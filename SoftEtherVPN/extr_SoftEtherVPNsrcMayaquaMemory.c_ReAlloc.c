#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int ZeroFree; scalar_t__ Size; int /*<<< orphan*/  Magic; } ;
typedef  TYPE_1__ MEMTAG ;

/* Variables and functions */
 int /*<<< orphan*/  CALC_MALLOCSIZE (scalar_t__) ; 
 int /*<<< orphan*/  CheckMemTag (TYPE_1__*) ; 
 int /*<<< orphan*/  Copy (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  Free (void*) ; 
 scalar_t__ IS_NULL_POINTER (void*) ; 
 TYPE_1__* InternalReAlloc (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMTAG_MAGIC ; 
 void* MEMTAG_TO_POINTER (TYPE_1__*) ; 
 void* MallocEx (scalar_t__,int) ; 
 TYPE_1__* POINTER_TO_MEMTAG (void*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void *ReAlloc(void *addr, UINT size)
{
	MEMTAG *tag;
	bool zerofree;
	// Validate arguments
	if (IS_NULL_POINTER(addr))
	{
		return NULL;
	}

	tag = POINTER_TO_MEMTAG(addr);
	CheckMemTag(tag);

	zerofree = tag->ZeroFree;

	if (tag->Size == size)
	{
		// No size change
		return addr;
	}
	else
	{
		if (zerofree)
		{
			// Size changed (zero clearing required)
			void *new_p = MallocEx(size, true);

			if (tag->Size <= size)
			{
				// Size expansion
				Copy(new_p, addr, tag->Size);
			}
			else
			{
				// Size reduction
				Copy(new_p, addr, size);
			}

			// Release the old block
			Free(addr);

			return new_p;
		}
		else
		{
			// Size changed
			MEMTAG *tag2 = InternalReAlloc(tag, CALC_MALLOCSIZE(size));

			Zero(tag2, sizeof(MEMTAG));
			tag2->Magic = MEMTAG_MAGIC;
			tag2->Size = size;

			return MEMTAG_TO_POINTER(tag2);
		}
	}
}