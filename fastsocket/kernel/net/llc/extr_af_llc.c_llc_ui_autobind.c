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
struct sockaddr_llc {int /*<<< orphan*/  sllc_arphrd; } ;
struct sock {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * mac; int /*<<< orphan*/  lsap; } ;
struct llc_sock {int /*<<< orphan*/  addr; TYPE_2__* dev; TYPE_1__ laddr; } ;
struct llc_sap {int dummy; } ;
struct TYPE_4__ {struct sockaddr_llc* dev_addr; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int EUSERS ; 
 int IFHWADDRLEN ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 TYPE_2__* dev_getfirstbyhwtype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  llc_sap_add_socket (struct llc_sap*,struct sock*) ; 
 struct llc_sap* llc_sap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct llc_sock* llc_sk (struct sock*) ; 
 int /*<<< orphan*/  llc_ui_autoport () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_llc*,int) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int llc_ui_autobind(struct socket *sock, struct sockaddr_llc *addr)
{
	struct sock *sk = sock->sk;
	struct llc_sock *llc = llc_sk(sk);
	struct llc_sap *sap;
	int rc = -EINVAL;

	if (!sock_flag(sk, SOCK_ZAPPED))
		goto out;
	rc = -ENODEV;
	llc->dev = dev_getfirstbyhwtype(&init_net, addr->sllc_arphrd);
	if (!llc->dev)
		goto out;
	rc = -EUSERS;
	llc->laddr.lsap = llc_ui_autoport();
	if (!llc->laddr.lsap)
		goto out;
	rc = -EBUSY; /* some other network layer is using the sap */
	sap = llc_sap_open(llc->laddr.lsap, NULL);
	if (!sap)
		goto out;
	memcpy(llc->laddr.mac, llc->dev->dev_addr, IFHWADDRLEN);
	memcpy(&llc->addr, addr, sizeof(llc->addr));
	/* assign new connection to its SAP */
	llc_sap_add_socket(sap, sk);
	sock_reset_flag(sk, SOCK_ZAPPED);
	rc = 0;
out:
	return rc;
}