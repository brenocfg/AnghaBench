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
typedef  int /*<<< orphan*/  uint64_t ;
struct kevent_qos_s {int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 size_t ENV_QOS_AFTER_OVERRIDE ; 
 int /*<<< orphan*/  EXPECT_QOS_EQ (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPECT_TEST_MSG (struct kevent_qos_s*) ; 
 int /*<<< orphan*/  T_END ; 
 int /*<<< orphan*/  T_EXPECT_LT (unsigned int,unsigned int,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/  T_SKIP (char*) ; 
 int /*<<< orphan*/  enable_kevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_expected_qos ; 
 int /*<<< orphan*/ * g_expected_qos_name ; 
 unsigned int get_user_promotion_basepri () ; 
 scalar_t__ geteuid () ; 

__attribute__((used)) static void
workloop_cb_test_sync_send_and_enable(uint64_t *workloop_id, struct kevent_qos_s **eventslist, int *events)
{
	unsigned override_priority;
	unsigned reenable_priority;

	T_LOG("Workloop handler workloop_cb_test_sync_send_and_enable called");

	EXPECT_TEST_MSG(*eventslist);

	if (geteuid() != 0) {
		T_SKIP("kevent_qos test requires root privileges to run.");
	}

	/* The effective Qos should be the one expected after override */
	EXPECT_QOS_EQ(g_expected_qos[ENV_QOS_AFTER_OVERRIDE],
			"dispatch_source event handler QoS should be %s", g_expected_qos_name[ENV_QOS_AFTER_OVERRIDE]);

	/* Snapshot the current override priority */
	override_priority = get_user_promotion_basepri();

	/* Enable the knote */
	struct kevent_qos_s *kev = *eventslist;
	enable_kevent(workloop_id, kev->ident);

	/*
	 * Check if the override has been dropped, check for priority instead of qos since
	 * there will be async qos push.
	 */
	reenable_priority = get_user_promotion_basepri();
	T_EXPECT_LT(reenable_priority, override_priority,
		"thread's current override priority %d should be less than override priority prior to enabling knote %d",
		reenable_priority, override_priority);

	*events = 0;
	T_END;
}