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
struct nf_conntrack_tuple_hash {int dummy; } ;
struct nf_conntrack_helper {int dummy; } ;
struct nf_conn_help {struct nf_conntrack_helper const* helper; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPCT_HELPER ; 
 int /*<<< orphan*/  nf_conntrack_event (int /*<<< orphan*/ ,struct nf_conn*) ; 
 struct nf_conn* nf_ct_tuplehash_to_ctrack (struct nf_conntrack_tuple_hash*) ; 
 struct nf_conn_help* nfct_help (struct nf_conn*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct nf_conntrack_helper const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int unhelp(struct nf_conntrack_tuple_hash *i,
			 const struct nf_conntrack_helper *me)
{
	struct nf_conn *ct = nf_ct_tuplehash_to_ctrack(i);
	struct nf_conn_help *help = nfct_help(ct);

	if (help && help->helper == me) {
		nf_conntrack_event(IPCT_HELPER, ct);
		rcu_assign_pointer(help->helper, NULL);
	}
	return 0;
}