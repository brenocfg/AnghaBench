#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t guint ;
struct TYPE_8__ {int /*<<< orphan*/  thr; } ;
typedef  TYPE_1__ chassis_event_thread_t ;
struct TYPE_10__ {int /*<<< orphan*/  message; } ;
struct TYPE_9__ {int len; TYPE_1__** pdata; } ;
typedef  int /*<<< orphan*/  GThreadFunc ;
typedef  TYPE_2__ GPtrArray ;
typedef  TYPE_3__ GError ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ chassis_event_thread_loop ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_error_free (TYPE_3__*) ; 
 int /*<<< orphan*/  g_message (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_thread_create (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__**) ; 

void chassis_event_threads_start(GPtrArray *threads) {
	guint i;

	g_message("%s: starting %d threads", G_STRLOC, threads->len - 1);

	for (i = 1; i < threads->len; i++) { /* the 1st is the main-thread and already set up */
		chassis_event_thread_t *thread = threads->pdata[i];
		GError *gerr = NULL;

		thread->thr = g_thread_create((GThreadFunc)chassis_event_thread_loop, thread, TRUE, &gerr);

		if (gerr) {
			g_critical("%s: %s", G_STRLOC, gerr->message);
			g_error_free(gerr);
			gerr = NULL;
		}
	}
}