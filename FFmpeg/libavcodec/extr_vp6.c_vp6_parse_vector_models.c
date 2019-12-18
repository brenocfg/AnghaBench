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
typedef  int /*<<< orphan*/  VP56RangeCoder ;
struct TYPE_4__ {void*** vector_fdv; void*** vector_pdv; void** vector_sig; void** vector_dct; } ;
typedef  TYPE_1__ VP56Model ;
struct TYPE_5__ {TYPE_1__* modelp; int /*<<< orphan*/  c; } ;
typedef  TYPE_2__ VP56Context ;

/* Variables and functions */
 scalar_t__ vp56_rac_get_prob_branchy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* vp56_rac_gets_nn (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** vp6_fdv_pct ; 
 int /*<<< orphan*/ ** vp6_pdv_pct ; 
 int /*<<< orphan*/ ** vp6_sig_dct_pct ; 

__attribute__((used)) static void vp6_parse_vector_models(VP56Context *s)
{
    VP56RangeCoder *c = &s->c;
    VP56Model *model = s->modelp;
    int comp, node;

    for (comp=0; comp<2; comp++) {
        if (vp56_rac_get_prob_branchy(c, vp6_sig_dct_pct[comp][0]))
            model->vector_dct[comp] = vp56_rac_gets_nn(c, 7);
        if (vp56_rac_get_prob_branchy(c, vp6_sig_dct_pct[comp][1]))
            model->vector_sig[comp] = vp56_rac_gets_nn(c, 7);
    }

    for (comp=0; comp<2; comp++)
        for (node=0; node<7; node++)
            if (vp56_rac_get_prob_branchy(c, vp6_pdv_pct[comp][node]))
                model->vector_pdv[comp][node] = vp56_rac_gets_nn(c, 7);

    for (comp=0; comp<2; comp++)
        for (node=0; node<8; node++)
            if (vp56_rac_get_prob_branchy(c, vp6_fdv_pct[comp][node]))
                model->vector_fdv[comp][node] = vp56_rac_gets_nn(c, 7);
}