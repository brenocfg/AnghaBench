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
struct socket {int dummy; } ;
struct sock {scalar_t__ sk_family; struct sk_security_struct* sk_security; } ;
struct sk_security_struct {int /*<<< orphan*/  sclass; int /*<<< orphan*/  sid; } ;
struct inode_security_struct {int /*<<< orphan*/  sclass; int /*<<< orphan*/  sid; } ;
struct TYPE_2__ {struct inode_security_struct* i_security; } ;

/* Variables and functions */
 scalar_t__ PF_INET ; 
 scalar_t__ PF_INET6 ; 
 scalar_t__ PF_UNIX ; 
 TYPE_1__* SOCK_INODE (struct socket*) ; 

__attribute__((used)) static void selinux_sock_graft(struct sock *sk, struct socket *parent)
{
	struct inode_security_struct *isec = SOCK_INODE(parent)->i_security;
	struct sk_security_struct *sksec = sk->sk_security;

	if (sk->sk_family == PF_INET || sk->sk_family == PF_INET6 ||
	    sk->sk_family == PF_UNIX)
		isec->sid = sksec->sid;
	sksec->sclass = isec->sclass;
}