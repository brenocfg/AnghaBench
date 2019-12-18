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
struct TYPE_3__ {int /*<<< orphan*/  timestamps; } ;
typedef  TYPE_1__ chassis_timestamps_t ;
typedef  int /*<<< orphan*/  chassis_timestamp_t ;

/* Variables and functions */
 int /*<<< orphan*/  chassis_timestamp_init_now (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * chassis_timestamp_new () ; 
 int /*<<< orphan*/  g_queue_push_tail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void chassis_timestamps_add(chassis_timestamps_t *ts,
		const char *name,
		const char *filename,
		gint line) {
	chassis_timestamp_t *t;

	t = chassis_timestamp_new();
	chassis_timestamp_init_now(t, name, filename, line);

	g_queue_push_tail(ts->timestamps, t);
}