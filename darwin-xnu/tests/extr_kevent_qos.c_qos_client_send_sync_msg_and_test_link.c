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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 size_t ENV_QOS_AFTER_OVERRIDE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KEVENT_QOS_SERVICE_NAME ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  T_ASSERT_FALSE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_MACH_SUCCESS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_TRUE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_END ; 
 int /*<<< orphan*/  T_LOG (char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 scalar_t__ _pthread_qos_class_encode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bootstrap_look_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bootstrap_port ; 
 int /*<<< orphan*/ * g_expected_qos ; 
 int /*<<< orphan*/  mach_sync_ipc_link_monitoring_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_sync_ipc_link_monitoring_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
qos_client_send_sync_msg_and_test_link(void *arg)
{
	mach_port_t qos_send_port;
	mach_port_t special_reply_port;
	boolean_t in_effect = FALSE;
	kern_return_t kr;
	unsigned long expected_result = (unsigned long) arg;

	kr = bootstrap_look_up(bootstrap_port,
			KEVENT_QOS_SERVICE_NAME, &qos_send_port);
	T_QUIET; T_ASSERT_MACH_SUCCESS(kr, "client bootstrap_look_up");

	/* start monitoring sync ipc link */
	kr = mach_sync_ipc_link_monitoring_start(&special_reply_port);
	T_QUIET; T_ASSERT_MACH_SUCCESS(kr, "mach_sync_ipc_link_monitoring_start");

	/* Send the message to msg port */
	send(qos_send_port, special_reply_port, MACH_PORT_NULL,
		(uint32_t)_pthread_qos_class_encode(g_expected_qos[ENV_QOS_AFTER_OVERRIDE], 0, 0), 0);

	/*
	 * wait for the reply
	 * some tests do not send a msg back so the receive
	 * might fail
	 */
	receive(special_reply_port, qos_send_port);

	/* stop monitoring link */
	kr = mach_sync_ipc_link_monitoring_stop(special_reply_port, &in_effect);
	T_QUIET; T_ASSERT_MACH_SUCCESS(kr, "mach_sync_ipc_link_monitoring_stop");

	if (!in_effect)
		T_LOG("Link was broken");
	else
		T_LOG("Link correct");

	if (expected_result == 1)
		T_ASSERT_TRUE(in_effect, "special reply port link after rcv");
	else
		T_ASSERT_FALSE(in_effect, "special reply port link after rcv");
	T_END;
}