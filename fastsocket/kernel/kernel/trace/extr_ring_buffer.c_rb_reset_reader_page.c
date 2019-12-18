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
struct ring_buffer_per_cpu {TYPE_2__* reader_page; int /*<<< orphan*/  read_stamp; } ;
struct TYPE_4__ {scalar_t__ read; TYPE_1__* page; } ;
struct TYPE_3__ {int /*<<< orphan*/  time_stamp; } ;

/* Variables and functions */

__attribute__((used)) static void rb_reset_reader_page(struct ring_buffer_per_cpu *cpu_buffer)
{
	cpu_buffer->read_stamp = cpu_buffer->reader_page->page->time_stamp;
	cpu_buffer->reader_page->read = 0;
}