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
struct ring_buffer_iter {int /*<<< orphan*/  head; int /*<<< orphan*/  head_page; } ;
struct ring_buffer_event {int dummy; } ;

/* Variables and functions */
 struct ring_buffer_event* __rb_page_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ring_buffer_event *
rb_iter_head_event(struct ring_buffer_iter *iter)
{
	return __rb_page_index(iter->head_page, iter->head);
}