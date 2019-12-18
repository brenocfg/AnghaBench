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
struct ring_buffer_per_cpu {int /*<<< orphan*/  commit_page; } ;

/* Variables and functions */
 int rb_page_commit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned
rb_commit_index(struct ring_buffer_per_cpu *cpu_buffer)
{
	return rb_page_commit(cpu_buffer->commit_page);
}