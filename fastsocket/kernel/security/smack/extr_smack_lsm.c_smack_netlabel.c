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
struct socket_smack {scalar_t__ smk_out; } ;
struct sock {int /*<<< orphan*/  sk_family; struct socket_smack* sk_security; } ;
struct netlbl_lsm_secattr {int dummy; } ;

/* Variables and functions */
 int SMACK_UNLABELED_SOCKET ; 
 int /*<<< orphan*/  bh_lock_sock_nested (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  netlbl_secattr_destroy (struct netlbl_lsm_secattr*) ; 
 int /*<<< orphan*/  netlbl_secattr_init (struct netlbl_lsm_secattr*) ; 
 int /*<<< orphan*/  netlbl_sock_delattr (struct sock*) ; 
 int netlbl_sock_setattr (struct sock*,int /*<<< orphan*/ ,struct netlbl_lsm_secattr*) ; 
 scalar_t__ smack_net_ambient ; 
 int /*<<< orphan*/  smack_to_secattr (scalar_t__,struct netlbl_lsm_secattr*) ; 

__attribute__((used)) static int smack_netlabel(struct sock *sk, int labeled)
{
	struct socket_smack *ssp = sk->sk_security;
	struct netlbl_lsm_secattr secattr;
	int rc = 0;

	/*
	 * Usually the netlabel code will handle changing the
	 * packet labeling based on the label.
	 * The case of a single label host is different, because
	 * a single label host should never get a labeled packet
	 * even though the label is usually associated with a packet
	 * label.
	 */
	local_bh_disable();
	bh_lock_sock_nested(sk);

	if (ssp->smk_out == smack_net_ambient ||
	    labeled == SMACK_UNLABELED_SOCKET)
		netlbl_sock_delattr(sk);
	else {
		netlbl_secattr_init(&secattr);
		smack_to_secattr(ssp->smk_out, &secattr);
		rc = netlbl_sock_setattr(sk, sk->sk_family, &secattr);
		netlbl_secattr_destroy(&secattr);
	}

	bh_unlock_sock(sk);
	local_bh_enable();

	return rc;
}