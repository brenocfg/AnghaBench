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
struct TYPE_5__ {scalar_t__ Magic; int /*<<< orphan*/  Size; scalar_t__ ZeroFree; } ;
typedef  TYPE_1__ MEMTAG ;

/* Variables and functions */
 int /*<<< orphan*/  CheckMemTag (TYPE_1__*) ; 
 scalar_t__ IS_NULL_POINTER (void*) ; 
 int /*<<< orphan*/  InternalFree (TYPE_1__*) ; 
 TYPE_1__* POINTER_TO_MEMTAG (void*) ; 
 int /*<<< orphan*/  Zero (void*,int /*<<< orphan*/ ) ; 

void Free(void *addr)
{
	MEMTAG *tag;
	// Validate arguments
	if (IS_NULL_POINTER(addr))
	{
		return;
	}

	tag = POINTER_TO_MEMTAG(addr);
	CheckMemTag(tag);

	if (tag->ZeroFree)
	{
		// Zero clear
		Zero(addr, tag->Size);
	}

	// Memory release
	tag->Magic = 0;
	InternalFree(tag);
}