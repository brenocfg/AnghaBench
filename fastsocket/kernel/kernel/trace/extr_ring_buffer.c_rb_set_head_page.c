#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ring_buffer_per_cpu {struct buffer_page* head_page; struct list_head* pages; } ;
struct list_head {TYPE_1__* prev; } ;
struct TYPE_4__ {int /*<<< orphan*/  prev; } ;
struct buffer_page {TYPE_2__ list; } ;
struct TYPE_3__ {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 scalar_t__ RB_WARN_ON (struct ring_buffer_per_cpu*,int) ; 
 int /*<<< orphan*/  rb_inc_page (struct ring_buffer_per_cpu*,struct buffer_page**) ; 
 scalar_t__ rb_is_head_page (struct ring_buffer_per_cpu*,struct buffer_page*,int /*<<< orphan*/ ) ; 
 struct list_head* rb_list_head (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct buffer_page *
rb_set_head_page(struct ring_buffer_per_cpu *cpu_buffer)
{
	struct buffer_page *head;
	struct buffer_page *page;
	struct list_head *list;
	int i;

	if (RB_WARN_ON(cpu_buffer, !cpu_buffer->head_page))
		return NULL;

	/* sanity check */
	list = cpu_buffer->pages;
	if (RB_WARN_ON(cpu_buffer, rb_list_head(list->prev->next) != list))
		return NULL;

	page = head = cpu_buffer->head_page;
	/*
	 * It is possible that the writer moves the header behind
	 * where we started, and we miss in one loop.
	 * A second loop should grab the header, but we'll do
	 * three loops just because I'm paranoid.
	 */
	for (i = 0; i < 3; i++) {
		do {
			if (rb_is_head_page(cpu_buffer, page, page->list.prev)) {
				cpu_buffer->head_page = page;
				return page;
			}
			rb_inc_page(cpu_buffer, &page);
		} while (page != head);
	}

	RB_WARN_ON(cpu_buffer, 1);

	return NULL;
}