#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* t_members; } ;
typedef  TYPE_1__ tdesc_t ;
struct TYPE_6__ {scalar_t__ ml_offset; scalar_t__ ml_size; struct TYPE_6__* ml_next; int /*<<< orphan*/  ml_type; int /*<<< orphan*/  ml_name; } ;
typedef  TYPE_2__ mlist_t ;
typedef  int /*<<< orphan*/  equiv_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  equiv_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
equiv_su(tdesc_t *stdp, tdesc_t *ttdp, equiv_data_t *ed)
{
	mlist_t *ml1 = stdp->t_members, *ml2 = ttdp->t_members;

	while (ml1 && ml2) {
		if (ml1->ml_offset != ml2->ml_offset ||
		    strcmp(ml1->ml_name, ml2->ml_name) != 0 ||
		    ml1->ml_size != ml2->ml_size ||
		    !equiv_node(ml1->ml_type, ml2->ml_type, ed))
			return (0);

		ml1 = ml1->ml_next;
		ml2 = ml2->ml_next;
	}

	if (ml1 || ml2)
		return (0);

	return (1);
}