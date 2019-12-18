#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  timestamps; } ;
typedef  TYPE_1__ chassis_timestamps_t ;
typedef  int /*<<< orphan*/  chassis_timestamp_t ;

/* Variables and functions */
 int /*<<< orphan*/  chassis_timestamp_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_queue_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_queue_pop_head (int /*<<< orphan*/ ) ; 

void chassis_timestamps_free(chassis_timestamps_t *ts) {
	chassis_timestamp_t *t;

	while ((t = g_queue_pop_head(ts->timestamps))) chassis_timestamp_free(t);
	g_queue_free(ts->timestamps);
	g_free(ts);
}