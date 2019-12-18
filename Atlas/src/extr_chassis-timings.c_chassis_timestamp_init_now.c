#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gint ;
struct TYPE_3__ {char const* name; char const* filename; int /*<<< orphan*/  ticks; int /*<<< orphan*/  cycles; int /*<<< orphan*/  usec; int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ chassis_timestamp_t ;

/* Variables and functions */
 int /*<<< orphan*/  my_timer_cycles () ; 
 int /*<<< orphan*/  my_timer_microseconds () ; 
 int /*<<< orphan*/  my_timer_ticks () ; 

void chassis_timestamp_init_now(chassis_timestamp_t *ts,
		const char *name,
		const char *filename,
		gint line) {

	ts->name = name;
	ts->filename = filename;
	ts->line = line;
	ts->usec = my_timer_microseconds();
	ts->cycles = my_timer_cycles();
	ts->ticks = my_timer_ticks();
}