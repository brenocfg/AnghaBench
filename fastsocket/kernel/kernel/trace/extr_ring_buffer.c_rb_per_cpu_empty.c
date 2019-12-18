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
struct ring_buffer_per_cpu {struct buffer_page* commit_page; struct buffer_page* reader_page; } ;
struct buffer_page {scalar_t__ read; } ;

/* Variables and functions */
 scalar_t__ rb_page_commit (struct buffer_page*) ; 
 struct buffer_page* rb_set_head_page (struct ring_buffer_per_cpu*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rb_per_cpu_empty(struct ring_buffer_per_cpu *cpu_buffer)
{
	struct buffer_page *reader = cpu_buffer->reader_page;
	struct buffer_page *head = rb_set_head_page(cpu_buffer);
	struct buffer_page *commit = cpu_buffer->commit_page;

	/* In case of error, head will be NULL */
	if (unlikely(!head))
		return 1;

	return reader->read == rb_page_commit(reader) &&
		(commit == reader ||
		 (commit == head &&
		  head->read == rb_page_commit(commit)));
}