#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sockaddr_sco {int /*<<< orphan*/  sco_bdaddr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct sock {scalar_t__ sk_state; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  src; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ AF_BLUETOOTH ; 
 int /*<<< orphan*/  BDADDR_ANY ; 
 scalar_t__ BT_BOUND ; 
 int /*<<< orphan*/  BT_DBG (char*,struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ BT_OPEN ; 
 int EADDRINUSE ; 
 int EBADFD ; 
 int EINVAL ; 
 scalar_t__ __sco_get_sock_by_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ bacmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batostr (int /*<<< orphan*/ *) ; 
 TYPE_2__* bt_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 TYPE_1__ sco_sk_list ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sco_sock_bind(struct socket *sock, struct sockaddr *addr, int addr_len)
{
	struct sockaddr_sco *sa = (struct sockaddr_sco *) addr;
	struct sock *sk = sock->sk;
	bdaddr_t *src = &sa->sco_bdaddr;
	int err = 0;

	BT_DBG("sk %p %s", sk, batostr(&sa->sco_bdaddr));

	if (!addr || addr->sa_family != AF_BLUETOOTH)
		return -EINVAL;

	lock_sock(sk);

	if (sk->sk_state != BT_OPEN) {
		err = -EBADFD;
		goto done;
	}

	write_lock_bh(&sco_sk_list.lock);

	if (bacmp(src, BDADDR_ANY) && __sco_get_sock_by_addr(src)) {
		err = -EADDRINUSE;
	} else {
		/* Save source address */
		bacpy(&bt_sk(sk)->src, &sa->sco_bdaddr);
		sk->sk_state = BT_BOUND;
	}

	write_unlock_bh(&sco_sk_list.lock);

done:
	release_sock(sk);
	return err;
}