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
 int /*<<< orphan*/  AF_RDS ; 
 int ENOMEM ; 
 int ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ SOCK_SEQPACKET ; 
 int __rds_create (struct socket*,struct sock*,int) ; 
 int /*<<< orphan*/  rds_proto ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rds_create(struct net *net, struct socket *sock, int protocol,
		      int kern)
{
	struct sock *sk;

	if (sock->type != SOCK_SEQPACKET || protocol)
		return -ESOCKTNOSUPPORT;

	sk = sk_alloc(net, AF_RDS, GFP_ATOMIC, &rds_proto);
	if (!sk)
		return -ENOMEM;

	return __rds_create(sock, sk, protocol);
}