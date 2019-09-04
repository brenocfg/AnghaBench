#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {scalar_t__ bank_count; TYPE_2__* bank_bitmap; } ;
typedef  TYPE_1__ hibernate_page_list_t ;
struct TYPE_6__ {scalar_t__ first_page; scalar_t__ last_page; size_t bitmapwords; int /*<<< orphan*/ * bitmap; } ;
typedef  TYPE_2__ hibernate_bitmap_t ;

/* Variables and functions */

hibernate_bitmap_t *
hibernate_page_bitmap_pin(hibernate_page_list_t * list, uint32_t * pPage)
{
    uint32_t             bank, page = *pPage;
    hibernate_bitmap_t * bitmap = &list->bank_bitmap[0];

    for (bank = 0; bank < list->bank_count; bank++)
    {
	if (page <= bitmap->first_page)
	{
	    *pPage = bitmap->first_page;
	    break;
	}
	if (page <= bitmap->last_page)
	    break;
	bitmap = (hibernate_bitmap_t *) &bitmap->bitmap[bitmap->bitmapwords];
    }
    if (bank == list->bank_count)
	bitmap = NULL;
	
    return (bitmap);
}