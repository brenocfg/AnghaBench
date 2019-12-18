#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {TYPE_2__* sk_prot; } ;
struct inet_hashinfo {int /*<<< orphan*/  bsockets; } ;
struct inet_bind_bucket {int /*<<< orphan*/  num_owners; int /*<<< orphan*/  owners; } ;
struct TYPE_8__ {struct inet_bind_bucket* icsk_bind_hash; } ;
struct TYPE_7__ {unsigned short num; } ;
struct TYPE_5__ {struct inet_hashinfo* hashinfo; } ;
struct TYPE_6__ {TYPE_1__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_4__* inet_csk (struct sock*) ; 
 TYPE_3__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  sk_add_bind_node (struct sock*,int /*<<< orphan*/ *) ; 

void inet_bind_hash(struct sock *sk, struct inet_bind_bucket *tb,
		    const unsigned short snum)
{
	struct inet_hashinfo *hashinfo = sk->sk_prot->h.hashinfo;

	atomic_inc(&hashinfo->bsockets);

	inet_sk(sk)->num = snum;
	sk_add_bind_node(sk, &tb->owners);
	tb->num_owners++;
	inet_csk(sk)->icsk_bind_hash = tb;
}