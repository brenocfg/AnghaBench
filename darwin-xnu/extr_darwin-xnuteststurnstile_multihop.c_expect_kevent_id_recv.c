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
typedef  int /*<<< orphan*/  pthread_workqueue_function_workloop_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_MACHPORT ; 
 int EV_ADD ; 
 int EV_DISPATCH ; 
 int EV_UDATA_SPECIFIC ; 
 int EV_VANISHED ; 
 int KEVENT_FLAG_ERROR_EVENTS ; 
 int KEVENT_FLAG_WORKLOOP ; 
 int /*<<< orphan*/  MACH_MSG_TRAILER_FORMAT_0 ; 
 int MACH_RCV_LARGE ; 
 int MACH_RCV_LARGE_IDENTITY ; 
 int MACH_RCV_MSG ; 
 int /*<<< orphan*/  MACH_RCV_TRAILER_CTX ; 
 int MACH_RCV_TRAILER_ELEMENTS (int /*<<< orphan*/ ) ; 
 int MACH_RCV_TRAILER_TYPE (int /*<<< orphan*/ ) ; 
 int MACH_RCV_VOUCHER ; 
 int /*<<< orphan*/  QOS_CLASS_MAINTENANCE ; 
 int /*<<< orphan*/  T_ASSERT_EQ (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_ZERO (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  _pthread_qos_class_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _pthread_workqueue_init_with_workloop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_cb ; 
 int kevent_id (int,struct kevent_qos_s*,int,struct kevent_qos_s*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  worker_cb ; 
 scalar_t__ workloop_cb_test_intransit ; 

__attribute__((used)) static void
expect_kevent_id_recv(mach_port_t port)
{
	int r;

	T_QUIET; T_ASSERT_POSIX_ZERO(_pthread_workqueue_init_with_workloop(
		worker_cb, event_cb,
		(pthread_workqueue_function_workloop_t)workloop_cb_test_intransit, 0, 0), NULL);

	struct kevent_qos_s kev[] = {{
		.ident = port,
		.filter = EVFILT_MACHPORT,
		.flags = EV_ADD | EV_UDATA_SPECIFIC | EV_DISPATCH | EV_VANISHED,
		.fflags = (MACH_RCV_MSG | MACH_RCV_LARGE | MACH_RCV_LARGE_IDENTITY |
				MACH_RCV_TRAILER_ELEMENTS(MACH_RCV_TRAILER_CTX) |
				MACH_RCV_TRAILER_TYPE(MACH_MSG_TRAILER_FORMAT_0) |
				MACH_RCV_VOUCHER),
		.data = 1,
		.qos = (int32_t)_pthread_qos_class_encode(QOS_CLASS_MAINTENANCE, 0, 0)
	}};

	struct kevent_qos_s kev_err[] = {{ 0 }};

	/* Setup workloop for mach msg rcv */
	r = kevent_id(25, kev, 1, kev_err, 1, NULL,
			NULL, KEVENT_FLAG_WORKLOOP | KEVENT_FLAG_ERROR_EVENTS);

	T_QUIET; T_ASSERT_POSIX_SUCCESS(r, "kevent_id");
	T_QUIET; T_ASSERT_EQ(r, 0, "no errors returned from kevent_id");
}