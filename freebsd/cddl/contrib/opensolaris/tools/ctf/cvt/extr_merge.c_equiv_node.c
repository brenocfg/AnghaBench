#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ t_emark; int t_id; scalar_t__ t_type; int /*<<< orphan*/  t_name; } ;
typedef  TYPE_1__ tdesc_t ;
struct TYPE_13__ {scalar_t__ ed_clear_mark; scalar_t__ ed_cur_mark; int /*<<< orphan*/  ed_selfuniquify; int /*<<< orphan*/  ed_ta; } ;
typedef  TYPE_4__ equiv_data_t ;
struct TYPE_14__ {int (* equiv ) (TYPE_1__*,TYPE_1__*,TYPE_4__*) ;} ;

/* Variables and functions */
 scalar_t__ FORWARD ; 
 int fwd_equiv (TYPE_1__*,TYPE_1__*) ; 
 int get_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* tdesc_ops ; 

__attribute__((used)) static int
equiv_node(tdesc_t *ctdp, tdesc_t *mtdp, equiv_data_t *ed)
{
	int (*equiv)(tdesc_t *, tdesc_t *, equiv_data_t *);
	int mapping;

	if (ctdp->t_emark > ed->ed_clear_mark &&
	    mtdp->t_emark > ed->ed_clear_mark)
		return (ctdp->t_emark == mtdp->t_emark);

	/*
	 * In normal (non-self-uniquify) mode, we don't want to do equivalency
	 * checking on a subgraph that has already been checked.  If a mapping
	 * has already been established for a given child node, we can simply
	 * compare the mapping for the child node with the ID of the parent
	 * node.  If we are in self-uniquify mode, then we're comparing two
	 * subgraphs within the child graph, and thus need to ignore any
	 * type mappings that have been created, as they are only valid into the
	 * parent.
	 */
	if ((mapping = get_mapping(ed->ed_ta, ctdp->t_id)) > 0 &&
	    mapping == mtdp->t_id && !ed->ed_selfuniquify)
		return (1);

	if (!streq(ctdp->t_name, mtdp->t_name))
		return (0);

	if (ctdp->t_type != mtdp->t_type) {
		if (ctdp->t_type == FORWARD || mtdp->t_type == FORWARD)
			return (fwd_equiv(ctdp, mtdp));
		else
			return (0);
	}

	ctdp->t_emark = ed->ed_cur_mark;
	mtdp->t_emark = ed->ed_cur_mark;
	ed->ed_cur_mark++;

	if ((equiv = tdesc_ops[ctdp->t_type].equiv) != NULL)
		return (equiv(ctdp, mtdp, ed));

	return (1);
}