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
struct rtentry {int dummy; } ;
struct radix_node_head {int dummy; } ;
struct radix_node {int dummy; } ;
typedef  int /*<<< orphan*/  rn_matchf_t ;

/* Variables and functions */
 int /*<<< orphan*/  RT_LOCK_SPIN (struct rtentry*) ; 
 int /*<<< orphan*/  RT_UNLOCK (struct rtentry*) ; 
 int /*<<< orphan*/  in_validate (struct radix_node*) ; 
 struct radix_node* rn_match_args (void*,struct radix_node_head*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static struct radix_node *
in_matroute_args(void *v_arg, struct radix_node_head *head,
    rn_matchf_t *f, void *w)
{
	struct radix_node *rn = rn_match_args(v_arg, head, f, w);

	if (rn != NULL) {
		RT_LOCK_SPIN((struct rtentry *)rn);
		in_validate(rn);
		RT_UNLOCK((struct rtentry *)rn);
	}
	return (rn);
}