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
typedef  int /*<<< orphan*/  mach_msg_return_t ;
struct TYPE_4__ {int /*<<< orphan*/  msgh_size; } ;
typedef  TYPE_1__ mach_msg_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  MACH_MSG_TIMEOUT_NONE ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int /*<<< orphan*/  MACH_SEND_MSG ; 
 int /*<<< orphan*/  mach_msg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

mach_msg_return_t
mach_msg_send(mach_msg_header_t *msg)
{
	return mach_msg(msg, MACH_SEND_MSG,
			msg->msgh_size, 0, MACH_PORT_NULL,
			MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}