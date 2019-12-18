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
struct linked_page {struct linked_page* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_image_page (struct linked_page*,int) ; 

__attribute__((used)) static inline void
free_list_of_pages(struct linked_page *list, int clear_page_nosave)
{
	while (list) {
		struct linked_page *lp = list->next;

		free_image_page(list, clear_page_nosave);
		list = lp;
	}
}