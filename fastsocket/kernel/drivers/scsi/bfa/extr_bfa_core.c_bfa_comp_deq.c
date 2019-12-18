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
struct list_head {int dummy; } ;
struct bfa_s {int /*<<< orphan*/  comp_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,struct list_head*) ; 

void
bfa_comp_deq(struct bfa_s *bfa, struct list_head *comp_q)
{
	INIT_LIST_HEAD(comp_q);
	list_splice_tail_init(&bfa->comp_q, comp_q);
}