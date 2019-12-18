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
struct socket {scalar_t__ type; } ;
struct sock {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_RAW ; 
 int EAFNOSUPPORT ; 
 int ENOMEM ; 
 int EPERM ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PF_LLC ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct net init_net ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  llc_proto ; 
 struct sock* llc_sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llc_ui_sk_init (struct socket*,struct sock*) ; 

__attribute__((used)) static int llc_ui_create(struct net *net, struct socket *sock, int protocol,
			 int kern)
{
	struct sock *sk;
	int rc = -ESOCKTNOSUPPORT;

	if (!capable(CAP_NET_RAW))
		return -EPERM;

	if (net != &init_net)
		return -EAFNOSUPPORT;

	if (likely(sock->type == SOCK_DGRAM || sock->type == SOCK_STREAM)) {
		rc = -ENOMEM;
		sk = llc_sk_alloc(net, PF_LLC, GFP_KERNEL, &llc_proto);
		if (sk) {
			rc = 0;
			llc_ui_sk_init(sock, sk);
		}
	}
	return rc;
}