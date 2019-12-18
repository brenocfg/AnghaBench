#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sl_num; unsigned int sl_max; TYPE_2__* sl_items; } ;
typedef  TYPE_1__ strlist_t ;
struct TYPE_7__ {char* si_str; unsigned int si_info; } ;
typedef  TYPE_2__ strlist_item_t ;

/* Variables and functions */
 TYPE_2__* bmake_realloc (TYPE_2__*,unsigned int) ; 

void
strlist_add_str(strlist_t *sl, char *str, unsigned int info)
{
	unsigned int n;
	strlist_item_t *items;

	if (str == NULL)
	    return;

	n = sl->sl_num + 1;
	sl->sl_num = n;
	items = sl->sl_items;
	if (n >= sl->sl_max) {
	    items = bmake_realloc(items, (n + 7) * sizeof *sl->sl_items);
	    sl->sl_items = items;
	    sl->sl_max = n + 6;
	}
	items += n - 1;
	items->si_str = str;
	items->si_info = info;
	items[1].si_str = NULL;         /* STRLIST_FOREACH() terminator */
}