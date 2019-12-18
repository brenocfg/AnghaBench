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
struct tcpip_callback_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMP_TCPIP_MSG_API ; 
 int /*<<< orphan*/  memp_free (int /*<<< orphan*/ ,struct tcpip_callback_msg*) ; 

void tcpip_callbackmsg_delete(struct tcpip_callback_msg* msg)
{
  memp_free(MEMP_TCPIP_MSG_API, msg);
}