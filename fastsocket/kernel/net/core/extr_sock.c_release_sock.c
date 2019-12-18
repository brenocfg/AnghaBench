#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  slock; int /*<<< orphan*/  wq; scalar_t__ owned; int /*<<< orphan*/  dep_map; } ;
struct TYPE_4__ {scalar_t__ tail; } ;
struct sock {TYPE_2__ sk_lock; TYPE_3__* sk_prot; TYPE_1__ sk_backlog; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* release_cb ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RHEL_PROTO_HAS_RELEASE_CB ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  __release_sock (struct sock*) ; 
 int /*<<< orphan*/  mutex_release (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ proto_has_rhel_ext (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void release_sock(struct sock *sk)
{
	/*
	 * The sk_lock has mutex_unlock() semantics:
	 */
	mutex_release(&sk->sk_lock.dep_map, 1, _RET_IP_);

	spin_lock_bh(&sk->sk_lock.slock);
	if (sk->sk_backlog.tail)
		__release_sock(sk);

	if (proto_has_rhel_ext(sk->sk_prot, RHEL_PROTO_HAS_RELEASE_CB) &&
	    sk->sk_prot->release_cb)
		sk->sk_prot->release_cb(sk);

	sk->sk_lock.owned = 0;
	if (waitqueue_active(&sk->sk_lock.wq))
		wake_up(&sk->sk_lock.wq);
	spin_unlock_bh(&sk->sk_lock.slock);
}