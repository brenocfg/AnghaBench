#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct l2cap_conn {int /*<<< orphan*/  hcon; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_2__ {scalar_t__ psm; int sec_level; struct l2cap_conn* conn; } ;

/* Variables and functions */
#define  BT_SECURITY_HIGH 129 
 int BT_SECURITY_LOW ; 
#define  BT_SECURITY_MEDIUM 128 
 int BT_SECURITY_SDP ; 
 int /*<<< orphan*/  HCI_AT_GENERAL_BONDING ; 
 int /*<<< orphan*/  HCI_AT_GENERAL_BONDING_MITM ; 
 int /*<<< orphan*/  HCI_AT_NO_BONDING ; 
 int /*<<< orphan*/  HCI_AT_NO_BONDING_MITM ; 
 scalar_t__ cpu_to_le16 (int) ; 
 int hci_conn_security (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* l2cap_pi (struct sock*) ; 

__attribute__((used)) static inline int l2cap_check_security(struct sock *sk)
{
	struct l2cap_conn *conn = l2cap_pi(sk)->conn;
	__u8 auth_type;

	if (l2cap_pi(sk)->psm == cpu_to_le16(0x0001)) {
		if (l2cap_pi(sk)->sec_level == BT_SECURITY_HIGH)
			auth_type = HCI_AT_NO_BONDING_MITM;
		else
			auth_type = HCI_AT_NO_BONDING;

		if (l2cap_pi(sk)->sec_level == BT_SECURITY_LOW)
			l2cap_pi(sk)->sec_level = BT_SECURITY_SDP;
	} else {
		switch (l2cap_pi(sk)->sec_level) {
		case BT_SECURITY_HIGH:
			auth_type = HCI_AT_GENERAL_BONDING_MITM;
			break;
		case BT_SECURITY_MEDIUM:
			auth_type = HCI_AT_GENERAL_BONDING;
			break;
		default:
			auth_type = HCI_AT_NO_BONDING;
			break;
		}
	}

	return hci_conn_security(conn->hcon, l2cap_pi(sk)->sec_level,
								auth_type);
}