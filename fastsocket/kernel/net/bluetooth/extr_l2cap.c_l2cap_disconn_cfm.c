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
struct hci_conn {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2cap_conn_del (struct hci_conn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int l2cap_disconn_cfm(struct hci_conn *hcon, u8 reason)
{
	BT_DBG("hcon %p reason %d", hcon, reason);

	if (hcon->type != ACL_LINK)
		return 0;

	l2cap_conn_del(hcon, bt_err(reason));

	return 0;
}