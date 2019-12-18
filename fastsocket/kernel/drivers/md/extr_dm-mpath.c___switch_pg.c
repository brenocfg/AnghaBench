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
struct pgpath {int /*<<< orphan*/  pg; } ;
struct multipath {int pg_init_required; int queue_io; scalar_t__ pg_init_count; scalar_t__ hw_handler_name; int /*<<< orphan*/  current_pg; } ;

/* Variables and functions */

__attribute__((used)) static void __switch_pg(struct multipath *m, struct pgpath *pgpath)
{
	m->current_pg = pgpath->pg;

	/* Must we initialise the PG first, and queue I/O till it's ready? */
	if (m->hw_handler_name) {
		m->pg_init_required = 1;
		m->queue_io = 1;
	} else {
		m->pg_init_required = 0;
		m->queue_io = 0;
	}

	m->pg_init_count = 0;
}