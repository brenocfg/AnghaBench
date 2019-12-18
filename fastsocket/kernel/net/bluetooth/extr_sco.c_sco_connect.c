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
struct sock {int /*<<< orphan*/  sk_sndtimeo; scalar_t__ sk_state; } ;
struct sco_conn {int /*<<< orphan*/  src; } ;
struct hci_dev {int dummy; } ;
struct hci_conn {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECT ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_SECURITY_LOW ; 
 int EHOSTUNREACH ; 
 int ENOMEM ; 
 int ESCO_LINK ; 
 int /*<<< orphan*/  HCI_AT_NO_BONDING ; 
 int SCO_LINK ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batostr (int /*<<< orphan*/ *) ; 
 TYPE_1__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  disable_esco ; 
 int /*<<< orphan*/  hci_conn_put (struct hci_conn*) ; 
 struct hci_conn* hci_connect (struct hci_dev*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock_bh (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock_bh (struct hci_dev*) ; 
 struct hci_dev* hci_get_route (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ lmp_esco_capable (struct hci_dev*) ; 
 int sco_chan_add (struct sco_conn*,struct sock*,int /*<<< orphan*/ *) ; 
 struct sco_conn* sco_conn_add (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sco_sock_clear_timer (struct sock*) ; 
 int /*<<< orphan*/  sco_sock_set_timer (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sco_connect(struct sock *sk)
{
	bdaddr_t *src = &bt_sk(sk)->src;
	bdaddr_t *dst = &bt_sk(sk)->dst;
	struct sco_conn *conn;
	struct hci_conn *hcon;
	struct hci_dev  *hdev;
	int err, type;

	BT_DBG("%s -> %s", batostr(src), batostr(dst));

	if (!(hdev = hci_get_route(dst, src)))
		return -EHOSTUNREACH;

	hci_dev_lock_bh(hdev);

	err = -ENOMEM;

	if (lmp_esco_capable(hdev) && !disable_esco)
		type = ESCO_LINK;
	else
		type = SCO_LINK;

	hcon = hci_connect(hdev, type, dst, BT_SECURITY_LOW, HCI_AT_NO_BONDING);
	if (!hcon)
		goto done;

	conn = sco_conn_add(hcon, 0);
	if (!conn) {
		hci_conn_put(hcon);
		goto done;
	}

	/* Update source addr of the socket */
	bacpy(src, conn->src);

	err = sco_chan_add(conn, sk, NULL);
	if (err)
		goto done;

	if (hcon->state == BT_CONNECTED) {
		sco_sock_clear_timer(sk);
		sk->sk_state = BT_CONNECTED;
	} else {
		sk->sk_state = BT_CONNECT;
		sco_sock_set_timer(sk, sk->sk_sndtimeo);
	}

done:
	hci_dev_unlock_bh(hdev);
	hci_dev_put(hdev);
	return err;
}