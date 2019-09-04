#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  Size; } ;
typedef  TYPE_1__ MEMTAG ;

/* Variables and functions */
 int /*<<< orphan*/  CheckMemTag (TYPE_1__*) ; 
 scalar_t__ IS_NULL_POINTER (void*) ; 
 TYPE_1__* POINTER_TO_MEMTAG (void*) ; 

UINT GetMemSize(void *addr)
{
	MEMTAG *tag;
	// Validate arguments
	if (IS_NULL_POINTER(addr))
	{
		return 0;
	}

	tag = POINTER_TO_MEMTAG(addr);
	CheckMemTag(tag);

	return tag->Size;
}