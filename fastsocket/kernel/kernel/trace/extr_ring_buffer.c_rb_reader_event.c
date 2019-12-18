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
struct ring_buffer_per_cpu {TYPE_1__* reader_page; } ;
struct ring_buffer_event {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  read; } ;

/* Variables and functions */
 struct ring_buffer_event* __rb_page_index (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ring_buffer_event *
rb_reader_event(struct ring_buffer_per_cpu *cpu_buffer)
{
	return __rb_page_index(cpu_buffer->reader_page,
			       cpu_buffer->reader_page->read);
}