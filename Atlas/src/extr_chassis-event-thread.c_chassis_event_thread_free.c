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
typedef  int /*<<< orphan*/  network_mysqld_con ;
struct TYPE_4__ {int notify_receive_fd; int notify_send_fd; int /*<<< orphan*/  event_queue; scalar_t__ event_base; int /*<<< orphan*/ * thr; int /*<<< orphan*/  notify_fd_event; } ;
typedef  TYPE_1__ chassis_event_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  closesocket (int) ; 
 int /*<<< orphan*/  event_base_free (scalar_t__) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_async_queue_try_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_async_queue_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_thread_join (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  network_mysqld_con_free (int /*<<< orphan*/ *) ; 

void chassis_event_thread_free(chassis_event_thread_t *thread) {
	if (!thread) return;

	if (thread->thr) g_thread_join(thread->thr);

	if (thread->notify_receive_fd != -1) {
		event_del(&(thread->notify_fd_event));
		closesocket(thread->notify_receive_fd);
	}
	if (thread->notify_send_fd != -1) {
		closesocket(thread->notify_send_fd);
	}

	/* we don't want to free the global event-base */
	if (thread->thr != NULL && thread->event_base) event_base_free(thread->event_base);

	network_mysqld_con* con;
	while (con = g_async_queue_try_pop(thread->event_queue)) {
		network_mysqld_con_free(con);
	}
	g_async_queue_unref(thread->event_queue);

	g_free(thread);
}