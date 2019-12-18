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
struct nf_conn {TYPE_1__* tuplehash; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuple; } ;

/* Variables and functions */
 size_t IP_CT_DIR_ORIGINAL ; 
 size_t IP_CT_DIR_REPLY ; 
 int /*<<< orphan*/  __nf_conntrack_hash_insert (struct nf_conn*,unsigned int,unsigned int) ; 
 unsigned int hash_conntrack (struct net*,int /*<<< orphan*/ *) ; 
 struct net* nf_ct_net (struct nf_conn*) ; 

void nf_conntrack_hash_insert(struct nf_conn *ct)
{
	struct net *net = nf_ct_net(ct);
	unsigned int hash, repl_hash;

	hash = hash_conntrack(net, &ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple);
	repl_hash = hash_conntrack(net, &ct->tuplehash[IP_CT_DIR_REPLY].tuple);

	__nf_conntrack_hash_insert(ct, hash, repl_hash);
}