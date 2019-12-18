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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_3__ {int /*<<< orphan*/  event_base; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ chassis_event_thread_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  GUINT_TO_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_STRLOC ; 
 scalar_t__ WSAGetLastError () ; 
 int /*<<< orphan*/  chassis_is_shutdown () ; 
 scalar_t__ errno ; 
 int event_base_dispatch (int /*<<< orphan*/ ) ; 
 scalar_t__ event_base_loopexit (int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  g_assert (int) ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  g_private_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strerror (scalar_t__) ; 
 int /*<<< orphan*/  tls_index ; 

void *chassis_event_thread_loop(chassis_event_thread_t *thread) {
	g_private_set(&tls_index, GUINT_TO_POINTER(thread->index));
	/**
	 * check once a second if we shall shutdown the proxy
	 */
	while (!chassis_is_shutdown()) {
		struct timeval timeout;
		int r;

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		g_assert(event_base_loopexit(thread->event_base, &timeout) == 0);

		r = event_base_dispatch(thread->event_base);

		if (r == -1) {
#ifdef WIN32
			errno = WSAGetLastError();
#endif
			if (errno == EINTR) continue;
			g_critical("%s: leaving chassis_event_thread_loop early, errno != EINTR was: %s (%d)", G_STRLOC, g_strerror(errno), errno);
			break;
		}
	}

	return NULL;
}