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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct llc_sock {int state; } ;
struct llc_conn_state_trans {int /*<<< orphan*/  (* ev_qualifiers ) (struct sock*,struct sk_buff*) ;int /*<<< orphan*/  (* ev ) (struct sock*,struct sk_buff*) ;} ;
struct llc_conn_state_ev {int /*<<< orphan*/  type; } ;
struct llc_conn_state {struct llc_conn_state_trans** transitions; } ;
typedef  int /*<<< orphan*/  (* llc_conn_ev_qfyr_t ) (struct sock*,struct sk_buff*) ;

/* Variables and functions */
 struct llc_conn_state_ev* llc_conn_ev (struct sk_buff*) ; 
 struct llc_conn_state* llc_conn_state_table ; 
 int llc_find_offset (int,int /*<<< orphan*/ ) ; 
 struct llc_sock* llc_sk (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static struct llc_conn_state_trans *llc_qualify_conn_ev(struct sock *sk,
							struct sk_buff *skb)
{
	struct llc_conn_state_trans **next_trans;
	llc_conn_ev_qfyr_t *next_qualifier;
	struct llc_conn_state_ev *ev = llc_conn_ev(skb);
	struct llc_sock *llc = llc_sk(sk);
	struct llc_conn_state *curr_state =
					&llc_conn_state_table[llc->state - 1];

	/* search thru events for this state until
	 * list exhausted or until no more
	 */
	for (next_trans = curr_state->transitions +
		llc_find_offset(llc->state - 1, ev->type);
	     (*next_trans)->ev; next_trans++) {
		if (!((*next_trans)->ev)(sk, skb)) {
			/* got POSSIBLE event match; the event may require
			 * qualification based on the values of a number of
			 * state flags; if all qualifications are met (i.e.,
			 * if all qualifying functions return success, or 0,
			 * then this is THE event we're looking for
			 */
			for (next_qualifier = (*next_trans)->ev_qualifiers;
			     next_qualifier && *next_qualifier &&
			     !(*next_qualifier)(sk, skb); next_qualifier++)
				/* nothing */;
			if (!next_qualifier || !*next_qualifier)
				/* all qualifiers executed successfully; this is
				 * our transition; return it so we can perform
				 * the associated actions & change the state
				 */
				return *next_trans;
		}
	}
	return NULL;
}