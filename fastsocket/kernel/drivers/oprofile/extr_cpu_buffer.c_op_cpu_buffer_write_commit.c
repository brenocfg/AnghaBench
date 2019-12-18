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
struct op_entry {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  op_ring_buffer ; 
 int ring_buffer_unlock_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int op_cpu_buffer_write_commit(struct op_entry *entry)
{
	return ring_buffer_unlock_commit(op_ring_buffer, entry->event);
}