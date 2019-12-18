#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int ZeroFree; int /*<<< orphan*/  Size; int /*<<< orphan*/  Magic; } ;
typedef  TYPE_1__ MEMTAG ;

/* Variables and functions */
 int /*<<< orphan*/  CALC_MALLOCSIZE (int /*<<< orphan*/ ) ; 
 TYPE_1__* InternalMalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMTAG_MAGIC ; 
 void* MEMTAG_TO_POINTER (TYPE_1__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void *MallocEx(UINT size, bool zero_clear_when_free)
{
	MEMTAG *tag;
	UINT real_size;

	real_size = CALC_MALLOCSIZE(size);

	tag = InternalMalloc(real_size);

	Zero(tag, sizeof(MEMTAG));
	tag->Magic = MEMTAG_MAGIC;
	tag->Size = size;
	tag->ZeroFree = zero_clear_when_free;

	return MEMTAG_TO_POINTER(tag);
}