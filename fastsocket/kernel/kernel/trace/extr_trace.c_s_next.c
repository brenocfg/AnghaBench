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
struct trace_iterator {int idx; scalar_t__ pos; } ;
struct seq_file {struct trace_iterator* private; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 void* find_next_entry_inc (struct trace_iterator*) ; 

__attribute__((used)) static void *s_next(struct seq_file *m, void *v, loff_t *pos)
{
	struct trace_iterator *iter = m->private;
	int i = (int)*pos;
	void *ent;

	(*pos)++;

	/* can't go backwards */
	if (iter->idx > i)
		return NULL;

	if (iter->idx < 0)
		ent = find_next_entry_inc(iter);
	else
		ent = iter;

	while (ent && iter->idx < i)
		ent = find_next_entry_inc(iter);

	iter->pos = *pos;

	return ent;
}