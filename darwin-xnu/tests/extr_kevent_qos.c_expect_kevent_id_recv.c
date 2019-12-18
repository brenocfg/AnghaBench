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
struct kevent_qos_s {int flags; int fflags; int data; int /*<<< orphan*/  member_0; int /*<<< orphan*/  qos; int /*<<< orphan*/  filter; int /*<<< orphan*/  ident; } ;
typedef  int /*<<< orphan*/  qos_class_t ;
typedef  int /*<<< orphan*/  pthread_workqueue_function_workloop_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 size_t ENV_QOS_QUEUE_OVERRIDE ; 
 int ENV_VAR_QOS ; 
 int /*<<< orphan*/  EVFILT_MACHPORT ; 
 int EV_ADD ; 
 int EV_DISPATCH ; 
 int EV_UDATA_SPECIFIC ; 
 int EV_VANISHED ; 
 int /*<<< orphan*/  HELPER_TIMEOUT_SECS ; 
 int KEVENT_FLAG_ERROR_EVENTS ; 
 int KEVENT_FLAG_WORKLOOP ; 
 int /*<<< orphan*/  MACH_MSG_TRAILER_FORMAT_0 ; 
 int MACH_RCV_LARGE ; 
 int MACH_RCV_LARGE_IDENTITY ; 
 int MACH_RCV_MSG ; 
 int /*<<< orphan*/  MACH_RCV_TRAILER_CTX ; 
 int MACH_RCV_TRAILER_ELEMENTS (int /*<<< orphan*/ ) ; 
 int MACH_RCV_TRAILER_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_ASSERT_EQ (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_FAIL (char*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_ZERO (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  _pthread_qos_class_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_workqueue_init_with_workloop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_cb ; 
 int /*<<< orphan*/ * g_expected_qos ; 
 char const** g_expected_qos_name ; 
 int kevent_id (int,struct kevent_qos_s*,int,struct kevent_qos_s*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  worker_cb ; 
 scalar_t__ workloop_cb_test_intransit ; 
 scalar_t__ workloop_cb_test_send_two_sync ; 
 scalar_t__ workloop_cb_test_sync_send ; 
 scalar_t__ workloop_cb_test_sync_send_and_enable ; 
 scalar_t__ workloop_cb_test_sync_send_deallocate ; 
 scalar_t__ workloop_cb_test_sync_send_do_nothing ; 
 scalar_t__ workloop_cb_test_sync_send_do_nothing_exit ; 
 scalar_t__ workloop_cb_test_sync_send_do_nothing_kevent_pthread ; 
 scalar_t__ workloop_cb_test_sync_send_kevent_reply ; 
 scalar_t__ workloop_cb_test_sync_send_kevent_reply_kevent_reply ; 
 scalar_t__ workloop_cb_test_sync_send_kevent_reply_reply_kevent ; 
 scalar_t__ workloop_cb_test_sync_send_reply ; 
 scalar_t__ workloop_cb_test_sync_send_reply_kevent ; 
 scalar_t__ workloop_cb_test_sync_send_reply_kevent_kevent_reply ; 
 scalar_t__ workloop_cb_test_sync_send_reply_kevent_pthread ; 
 scalar_t__ workloop_cb_test_sync_send_reply_kevent_reply_kevent ; 
 scalar_t__ workloop_cb_test_two_send_and_destroy ; 

__attribute__((used)) static void
expect_kevent_id_recv(mach_port_t port, qos_class_t qos[], const char *qos_name[], const char *wl_function)
{
	int r;

	/* Qos expected by workloop thread */
	for (int i = 0; i < ENV_VAR_QOS; i++) {
		g_expected_qos[i] = qos[i];
		g_expected_qos_name[i] = qos_name[i];
	}

	if (strcmp(wl_function, "workloop_cb_test_intransit") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_intransit, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_sync_send") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_sync_send, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_sync_send_and_enable") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_sync_send_and_enable, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_send_two_sync") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_send_two_sync, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_two_send_and_destroy") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_two_send_and_destroy, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_sync_send_reply") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_sync_send_reply, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_sync_send_deallocate") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_sync_send_deallocate, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_sync_send_reply_kevent") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_sync_send_reply_kevent, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_sync_send_reply_kevent_pthread") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_sync_send_reply_kevent_pthread, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_sync_send_kevent_reply") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_sync_send_kevent_reply, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_sync_send_do_nothing") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_sync_send_do_nothing, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_sync_send_do_nothing_kevent_pthread") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_sync_send_do_nothing_kevent_pthread, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_sync_send_do_nothing_exit") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_sync_send_do_nothing_exit, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_sync_send_reply_kevent_reply_kevent") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_sync_send_reply_kevent_reply_kevent, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_sync_send_kevent_reply_reply_kevent") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_sync_send_kevent_reply_reply_kevent, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_sync_send_kevent_reply_kevent_reply") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_sync_send_kevent_reply_kevent_reply, 0, 0), NULL);
	} else if (strcmp(wl_function, "workloop_cb_test_sync_send_reply_kevent_kevent_reply") == 0) {
		T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
			worker_cb, event_cb,
			(pthread_workqueue_function_workloop_t)workloop_cb_test_sync_send_reply_kevent_kevent_reply, 0, 0), NULL);
	} else {
		T_ASSERT_FAIL("no workloop function specified \n");
	}

	struct kevent_qos_s kev[] = {{
		.ident = port,
		.filter = EVFILT_MACHPORT,
		.flags = EV_ADD | EV_UDATA_SPECIFIC | EV_DISPATCH | EV_VANISHED,
		.fflags = (MACH_RCV_MSG | MACH_RCV_LARGE | MACH_RCV_LARGE_IDENTITY |
				MACH_RCV_TRAILER_ELEMENTS(MACH_RCV_TRAILER_CTX) |
				MACH_RCV_TRAILER_TYPE(MACH_MSG_TRAILER_FORMAT_0)),
		.data = 1,
		.qos = (int32_t)_pthread_qos_class_encode(qos[ENV_QOS_QUEUE_OVERRIDE], 0, 0)
	}};

	struct kevent_qos_s kev_err[] = {{ 0 }};

	/* Setup workloop for mach msg rcv */
	r = kevent_id(25, kev, 1, kev_err, 1, NULL,
			NULL, KEVENT_FLAG_WORKLOOP | KEVENT_FLAG_ERROR_EVENTS);

	T_QUIET; T_ASSERT_POSIX_SUCCESS(r, "kevent_id");
	T_QUIET; T_ASSERT_EQ(r, 0, "no errors returned from kevent_id");
	sleep(HELPER_TIMEOUT_SECS);
}