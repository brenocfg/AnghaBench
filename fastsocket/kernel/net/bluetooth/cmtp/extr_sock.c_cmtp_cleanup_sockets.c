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

/* Variables and functions */
 int /*<<< orphan*/  BTPROTO_CMTP ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 scalar_t__ bt_sock_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmtp_proto ; 
 int /*<<< orphan*/  proto_unregister (int /*<<< orphan*/ *) ; 

void cmtp_cleanup_sockets(void)
{
	if (bt_sock_unregister(BTPROTO_CMTP) < 0)
		BT_ERR("Can't unregister CMTP socket");

	proto_unregister(&cmtp_proto);
}