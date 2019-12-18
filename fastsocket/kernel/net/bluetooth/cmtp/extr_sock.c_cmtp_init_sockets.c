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
 int bt_sock_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmtp_proto ; 
 int /*<<< orphan*/  cmtp_sock_family_ops ; 
 int proto_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_unregister (int /*<<< orphan*/ *) ; 

int cmtp_init_sockets(void)
{
	int err;

	err = proto_register(&cmtp_proto, 0);
	if (err < 0)
		return err;

	err = bt_sock_register(BTPROTO_CMTP, &cmtp_sock_family_ops);
	if (err < 0)
		goto error;

	return 0;

error:
	BT_ERR("Can't register CMTP socket");
	proto_unregister(&cmtp_proto);
	return err;
}