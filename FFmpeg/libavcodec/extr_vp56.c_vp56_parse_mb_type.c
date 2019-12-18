#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t VP56mb ;
typedef  int /*<<< orphan*/  VP56RangeCoder ;
struct TYPE_5__ {int /*<<< orphan*/  c; TYPE_1__* modelp; } ;
typedef  TYPE_2__ VP56Context ;
struct TYPE_4__ {int /*<<< orphan*/ *** mb_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ff_vp56_pmbt_tree ; 
 scalar_t__ vp56_rac_get_prob_branchy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t vp56_rac_get_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VP56mb vp56_parse_mb_type(VP56Context *s,
                                 VP56mb prev_type, int ctx)
{
    uint8_t *mb_type_model = s->modelp->mb_type[ctx][prev_type];
    VP56RangeCoder *c = &s->c;

    if (vp56_rac_get_prob_branchy(c, mb_type_model[0]))
        return prev_type;
    else
        return vp56_rac_get_tree(c, ff_vp56_pmbt_tree, mb_type_model);
}