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
struct nf_conn {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPCT_DESTROY ; 
 int /*<<< orphan*/  IPS_DYING_BIT ; 
 scalar_t__ nf_conntrack_event (int /*<<< orphan*/ ,struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_delete_from_lists (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_insert_dying_list (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_put (struct nf_conn*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void death_by_timeout(unsigned long ul_conntrack)
{
	struct nf_conn *ct = (void *)ul_conntrack;

	if (!test_bit(IPS_DYING_BIT, &ct->status) &&
	    unlikely(nf_conntrack_event(IPCT_DESTROY, ct) < 0)) {
		/* destroy event was not delivered */
		nf_ct_delete_from_lists(ct);
		nf_ct_insert_dying_list(ct);
		return;
	}
	set_bit(IPS_DYING_BIT, &ct->status);
	nf_ct_delete_from_lists(ct);
	nf_ct_put(ct);
}