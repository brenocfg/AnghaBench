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
struct op_entry {int size; unsigned long* data; } ;

/* Variables and functions */

__attribute__((used)) static inline
int op_cpu_buffer_get_data(struct op_entry *entry, unsigned long *val)
{
	int size = entry->size;
	if (!size)
		return 0;
	*val = *entry->data;
	entry->size--;
	entry->data++;
	return size;
}