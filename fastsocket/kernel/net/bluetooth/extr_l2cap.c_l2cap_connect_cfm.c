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
typedef  int /*<<< orphan*/  u8 ;
struct l2cap_conn {int dummy; } ;
struct hci_conn {scalar_t__ type; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batostr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_err (int /*<<< orphan*/ ) ; 
 struct l2cap_conn* l2cap_conn_add (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_conn_del (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_conn_ready (struct l2cap_conn*) ; 

__attribute__((used)) static int l2cap_connect_cfm(struct hci_conn *hcon, u8 status)
{
	struct l2cap_conn *conn;

	BT_DBG("hcon %p bdaddr %s status %d", hcon, batostr(&hcon->dst), status);

	if (hcon->type != ACL_LINK)
		return 0;

	if (!status) {
		conn = l2cap_conn_add(hcon, status);
		if (conn)
			l2cap_conn_ready(conn);
	} else
		l2cap_conn_del(hcon, bt_err(status));

	return 0;
}