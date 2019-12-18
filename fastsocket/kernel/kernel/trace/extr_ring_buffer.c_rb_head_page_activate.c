#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ring_buffer_per_cpu {struct buffer_page* head_page; } ;
struct TYPE_2__ {int /*<<< orphan*/  prev; } ;
struct buffer_page {TYPE_1__ list; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_set_list_to_head (struct ring_buffer_per_cpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rb_head_page_activate(struct ring_buffer_per_cpu *cpu_buffer)
{
	struct buffer_page *head;

	head = cpu_buffer->head_page;
	if (!head)
		return;

	/*
	 * Set the previous list pointer to have the HEAD flag.
	 */
	rb_set_list_to_head(cpu_buffer, head->list.prev);
}