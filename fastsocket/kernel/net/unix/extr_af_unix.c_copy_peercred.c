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
struct TYPE_2__ {scalar_t__ sk_peer_cred; int /*<<< orphan*/  sk_peer_pid; } ;

/* Variables and functions */
 scalar_t__ get_cred (scalar_t__) ; 
 int /*<<< orphan*/  get_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cred (scalar_t__) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 TYPE_1__* sk_extended (struct sock*) ; 

__attribute__((used)) static void copy_peercred(struct sock *sk, struct sock *peersk)
{
	put_pid(sk_extended(sk)->sk_peer_pid);
	if (sk_extended(sk)->sk_peer_cred)
		put_cred(sk_extended(sk)->sk_peer_cred);
	sk_extended(sk)->sk_peer_pid  = get_pid(sk_extended(peersk)->sk_peer_pid);
	sk_extended(sk)->sk_peer_cred = get_cred(sk_extended(peersk)->sk_peer_cred);
}