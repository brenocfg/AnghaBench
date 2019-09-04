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
struct kevent_qos_s {scalar_t__* ext; } ;
typedef  int mach_port_type_t ;
typedef  int mach_port_t ;
struct TYPE_3__ {int msgh_remote_port; } ;
typedef  TYPE_1__ mach_msg_header_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int MACH_PORT_TYPE_SEND_ONCE ; 
 int MACH_PORT_VALID (int) ; 
 int /*<<< orphan*/  T_ASSERT_MACH_SUCCESS (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_NOTNULL (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  T_ASSERT_TRUE (int,char*) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  mach_port_type (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  mach_task_self () ; 

__attribute__((used)) static mach_port_type_t
get_reply_port(struct kevent_qos_s *kev)
{
	mach_msg_header_t *hdr;
	mach_port_t reply_port;
	mach_port_type_t type;
	kern_return_t kr;

	hdr = (void*)kev->ext[0];
	T_QUIET; T_ASSERT_NOTNULL(hdr, "msg hdr");

	reply_port = hdr->msgh_remote_port;
	T_QUIET;T_ASSERT_TRUE(MACH_PORT_VALID(reply_port), "reply port valid");
	kr = mach_port_type(mach_task_self(), reply_port, &type);
	T_QUIET; T_ASSERT_MACH_SUCCESS(kr, "mach_port_type");
	T_QUIET; T_ASSERT_TRUE(type & MACH_PORT_TYPE_SEND_ONCE, "send once received");

	return reply_port;
}