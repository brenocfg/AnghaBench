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
struct TYPE_4__ {int notify_receive_fd; int notify_send_fd; int /*<<< orphan*/  notify_fd_event; int /*<<< orphan*/  event_base; int /*<<< orphan*/ * chas; } ;
typedef  TYPE_1__ chassis_event_thread_t ;
typedef  int /*<<< orphan*/  chassis ;

/* Variables and functions */
 int EV_PERSIST ; 
 int EV_READ ; 
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  chassis_event_handle ; 
 int errno ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_base_new () ; 
 int /*<<< orphan*/  event_base_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  g_error (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_strerror (int) ; 
 scalar_t__ pipe (int*) ; 

int chassis_event_threads_init_thread(chassis_event_thread_t *thread, chassis *chas) {
	thread->event_base = event_base_new();
	thread->chas = chas;

	int fds[2];
	if (pipe(fds)) {
		int err;
		err = errno;
		g_error("%s: evutil_socketpair() failed: %s (%d)", 
				G_STRLOC,
				g_strerror(err),
				err);
	}
	thread->notify_receive_fd = fds[0];
	thread->notify_send_fd = fds[1];

	event_set(&(thread->notify_fd_event), thread->notify_receive_fd, EV_READ | EV_PERSIST, chassis_event_handle, thread);
	event_base_set(thread->event_base, &(thread->notify_fd_event));
	event_add(&(thread->notify_fd_event), NULL);

	return 0;
}