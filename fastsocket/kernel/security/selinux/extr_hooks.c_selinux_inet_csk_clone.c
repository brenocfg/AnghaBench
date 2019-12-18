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
struct sock {struct sk_security_struct* sk_security; } ;
struct sk_security_struct {int /*<<< orphan*/  peer_sid; int /*<<< orphan*/  sid; } ;
struct request_sock {TYPE_1__* rsk_ops; int /*<<< orphan*/  peer_secid; int /*<<< orphan*/  secid; } ;
struct TYPE_2__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  selinux_netlbl_inet_csk_clone (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void selinux_inet_csk_clone(struct sock *newsk,
				   const struct request_sock *req)
{
	struct sk_security_struct *newsksec = newsk->sk_security;

	newsksec->sid = req->secid;
	newsksec->peer_sid = req->peer_secid;
	/* NOTE: Ideally, we should also get the isec->sid for the
	   new socket in sync, but we don't have the isec available yet.
	   So we will wait until sock_graft to do it, by which
	   time it will have been created and available. */

	/* We don't need to take any sort of lock here as we are the only
	 * thread with access to newsksec */
	selinux_netlbl_inet_csk_clone(newsk, req->rsk_ops->family);
}