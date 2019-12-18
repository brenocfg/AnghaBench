#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  t_id; } ;
typedef  TYPE_1__ tdesc_t ;
struct TYPE_7__ {TYPE_1__* ed_tgt; scalar_t__ ed_clear_mark; scalar_t__ ed_cur_mark; TYPE_1__* ed_node; } ;
typedef  TYPE_2__ equiv_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ equiv_node (TYPE_1__*,TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int
equiv_cb(void *bucket, void *arg)
{
	equiv_data_t *ed = arg;
	tdesc_t *mtdp = bucket;
	tdesc_t *ctdp = ed->ed_node;

	ed->ed_clear_mark = ed->ed_cur_mark + 1;
	ed->ed_cur_mark = ed->ed_clear_mark + 1;

	if (equiv_node(ctdp, mtdp, ed)) {
		debug(3, "equiv_node matched %d <%x> %d <%x>\n",
		    ctdp->t_id, ctdp->t_id, mtdp->t_id, mtdp->t_id);
		ed->ed_tgt = mtdp;
		/* matched.  stop looking */
		return (-1);
	}

	return (0);
}