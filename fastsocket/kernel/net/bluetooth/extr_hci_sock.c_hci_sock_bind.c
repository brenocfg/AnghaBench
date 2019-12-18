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
struct socket {struct sock* sk; } ;
struct sockaddr_hci {scalar_t__ hci_family; scalar_t__ hci_dev; } ;
struct sockaddr {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_state; } ;
struct hci_dev {int /*<<< orphan*/  promisc; } ;
struct TYPE_2__ {struct hci_dev* hdev; } ;

/* Variables and functions */
 scalar_t__ AF_BLUETOOTH ; 
 int /*<<< orphan*/  BT_BOUND ; 
 int /*<<< orphan*/  BT_DBG (char*,struct socket*,struct sock*) ; 
 int EALREADY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ HCI_DEV_NONE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct hci_dev* hci_dev_get (scalar_t__) ; 
 TYPE_1__* hci_pi (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int hci_sock_bind(struct socket *sock, struct sockaddr *addr, int addr_len)
{
	struct sockaddr_hci *haddr = (struct sockaddr_hci *) addr;
	struct sock *sk = sock->sk;
	struct hci_dev *hdev = NULL;
	int err = 0;

	BT_DBG("sock %p sk %p", sock, sk);

	if (!haddr || haddr->hci_family != AF_BLUETOOTH)
		return -EINVAL;

	lock_sock(sk);

	if (hci_pi(sk)->hdev) {
		err = -EALREADY;
		goto done;
	}

	if (haddr->hci_dev != HCI_DEV_NONE) {
		if (!(hdev = hci_dev_get(haddr->hci_dev))) {
			err = -ENODEV;
			goto done;
		}

		atomic_inc(&hdev->promisc);
	}

	hci_pi(sk)->hdev = hdev;
	sk->sk_state = BT_BOUND;

done:
	release_sock(sk);
	return err;
}