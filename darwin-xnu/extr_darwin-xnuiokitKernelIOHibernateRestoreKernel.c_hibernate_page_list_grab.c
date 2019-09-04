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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ ppnum_t ;
typedef  int /*<<< orphan*/  hibernate_page_list_t ;
struct TYPE_4__ {scalar_t__ last_page; } ;
typedef  TYPE_1__ hibernate_bitmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  debug_code (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fatal () ; 
 scalar_t__ hibernate_page_bitmap_count (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* hibernate_page_bitmap_pin (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  kIOHibernateRestoreCodeNoMemory ; 

__attribute__((used)) static ppnum_t
hibernate_page_list_grab(hibernate_page_list_t * list, uint32_t * pNextFree)
{
    uint32_t		 nextFree = *pNextFree;
    uint32_t		 nextFreeInBank;
    hibernate_bitmap_t * bitmap;

    nextFreeInBank = nextFree + 1;
    while ((bitmap = hibernate_page_bitmap_pin(list, &nextFreeInBank)))
    {
	nextFreeInBank += hibernate_page_bitmap_count(bitmap, FALSE, nextFreeInBank);
	if (nextFreeInBank <= bitmap->last_page)
	{
	    *pNextFree = nextFreeInBank;
	    break;
	}
    }

    if (!bitmap) 
    {
	debug_code(kIOHibernateRestoreCodeNoMemory, nextFree);
	fatal();
	nextFree = 0;
    }

    return (nextFree);
}