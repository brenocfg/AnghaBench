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
struct sock {int dummy; } ;
struct sctp_bind_hashbucket {int /*<<< orphan*/  lock; } ;
struct sctp_bind_bucket {int dummy; } ;
struct TYPE_4__ {scalar_t__ num; } ;
struct TYPE_3__ {struct sctp_bind_bucket* bind_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sk_del_bind_node (struct sock*) ; 
 TYPE_2__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  sctp_bucket_destroy (struct sctp_bind_bucket*) ; 
 size_t sctp_phashfn (scalar_t__) ; 
 struct sctp_bind_hashbucket* sctp_port_hashtable ; 
 TYPE_1__* sctp_sk (struct sock*) ; 
 int /*<<< orphan*/  sctp_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __sctp_put_port(struct sock *sk)
{
	struct sctp_bind_hashbucket *head =
		&sctp_port_hashtable[sctp_phashfn(inet_sk(sk)->num)];
	struct sctp_bind_bucket *pp;

	sctp_spin_lock(&head->lock);
	pp = sctp_sk(sk)->bind_hash;
	__sk_del_bind_node(sk);
	sctp_sk(sk)->bind_hash = NULL;
	inet_sk(sk)->num = 0;
	sctp_bucket_destroy(pp);
	sctp_spin_unlock(&head->lock);
}