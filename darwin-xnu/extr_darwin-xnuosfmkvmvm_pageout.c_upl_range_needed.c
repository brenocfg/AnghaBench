#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* upl_t ;
struct TYPE_5__ {int /*<<< orphan*/  needed; } ;
typedef  TYPE_2__ upl_page_info_t ;
struct upl {int dummy; } ;
struct TYPE_4__ {int flags; int size; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int UPL_INTERNAL ; 

void
upl_range_needed(
	upl_t		upl,
	int		index,
	int		count)
{
	upl_page_info_t	*user_page_list;
	int		size_in_pages;

	if ( !(upl->flags & UPL_INTERNAL) || count <= 0)
		return;

	size_in_pages = upl->size / PAGE_SIZE;

	user_page_list = (upl_page_info_t *) (((uintptr_t)upl) + sizeof(struct upl));

	while (count-- && index < size_in_pages)
		user_page_list[index++].needed = TRUE;
}