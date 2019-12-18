#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct page_list {scalar_t__ next; } ;
struct dpages {scalar_t__ context_u; scalar_t__ context_ptr; } ;

/* Variables and functions */

__attribute__((used)) static void list_next_page(struct dpages *dp)
{
	struct page_list *pl = (struct page_list *) dp->context_ptr;
	dp->context_ptr = pl->next;
	dp->context_u = 0;
}