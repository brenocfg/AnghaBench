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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  hibernate_page_list_t ;
struct TYPE_3__ {int* bitmap; scalar_t__ first_page; } ;
typedef  TYPE_1__ hibernate_bitmap_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 TYPE_1__* hibernate_page_bitmap (int /*<<< orphan*/ *,int) ; 

void 
hibernate_page_bitset(hibernate_page_list_t * list, boolean_t set, uint32_t page)
{
    hibernate_bitmap_t * bitmap;

    bitmap = hibernate_page_bitmap(list, page);
    if (bitmap)
    {
	page -= bitmap->first_page;
	if (set)
	    bitmap->bitmap[page >> 5] |= (0x80000000 >> (page & 31));
	    //setbit(page - bitmap->first_page, (int *) &bitmap->bitmap[0]);
	else
	    bitmap->bitmap[page >> 5] &= ~(0x80000000 >> (page & 31));
	    //clrbit(page - bitmap->first_page, (int *) &bitmap->bitmap[0]);
    }
}