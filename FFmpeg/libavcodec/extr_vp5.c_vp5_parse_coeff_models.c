#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  def_prob ;
typedef  int /*<<< orphan*/  VP56RangeCoder ;
struct TYPE_6__ {int** coeff_dccv; int**** coeff_ract; void****** coeff_acct; void**** coeff_dcct; } ;
typedef  TYPE_2__ VP56Model ;
struct TYPE_7__ {TYPE_1__** frames; TYPE_2__* modelp; int /*<<< orphan*/  c; } ;
typedef  TYPE_3__ VP56Context ;
struct TYPE_5__ {scalar_t__ key_frame; } ;

/* Variables and functions */
 size_t VP56_FRAME_CURRENT ; 
 void* av_clip (int,int,int) ; 
 int /*<<< orphan*/  memset (void**,int,int) ; 
 scalar_t__ vp56_rac_get_prob_branchy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* vp56_rac_gets_nn (int /*<<< orphan*/ *,int) ; 
 int*** vp5_dccv_lc ; 
 int /*<<< orphan*/ ** vp5_dccv_pct ; 
 int***** vp5_ract_lc ; 
 int /*<<< orphan*/ **** vp5_ract_pct ; 

__attribute__((used)) static int vp5_parse_coeff_models(VP56Context *s)
{
    VP56RangeCoder *c = &s->c;
    VP56Model *model = s->modelp;
    uint8_t def_prob[11];
    int node, cg, ctx;
    int ct;    /* code type */
    int pt;    /* plane type (0 for Y, 1 for U or V) */

    memset(def_prob, 0x80, sizeof(def_prob));

    for (pt=0; pt<2; pt++)
        for (node=0; node<11; node++)
            if (vp56_rac_get_prob_branchy(c, vp5_dccv_pct[pt][node])) {
                def_prob[node] = vp56_rac_gets_nn(c, 7);
                model->coeff_dccv[pt][node] = def_prob[node];
            } else if (s->frames[VP56_FRAME_CURRENT]->key_frame) {
                model->coeff_dccv[pt][node] = def_prob[node];
            }

    for (ct=0; ct<3; ct++)
        for (pt=0; pt<2; pt++)
            for (cg=0; cg<6; cg++)
                for (node=0; node<11; node++)
                    if (vp56_rac_get_prob_branchy(c, vp5_ract_pct[ct][pt][cg][node])) {
                        def_prob[node] = vp56_rac_gets_nn(c, 7);
                        model->coeff_ract[pt][ct][cg][node] = def_prob[node];
                    } else if (s->frames[VP56_FRAME_CURRENT]->key_frame) {
                        model->coeff_ract[pt][ct][cg][node] = def_prob[node];
                    }

    /* coeff_dcct is a linear combination of coeff_dccv */
    for (pt=0; pt<2; pt++)
        for (ctx=0; ctx<36; ctx++)
            for (node=0; node<5; node++)
                model->coeff_dcct[pt][ctx][node] = av_clip(((model->coeff_dccv[pt][node] * vp5_dccv_lc[node][ctx][0] + 128) >> 8) + vp5_dccv_lc[node][ctx][1], 1, 254);

    /* coeff_acct is a linear combination of coeff_ract */
    for (ct=0; ct<3; ct++)
        for (pt=0; pt<2; pt++)
            for (cg=0; cg<3; cg++)
                for (ctx=0; ctx<6; ctx++)
                    for (node=0; node<5; node++)
                        model->coeff_acct[pt][ct][cg][ctx][node] = av_clip(((model->coeff_ract[pt][ct][cg][node] * vp5_ract_lc[ct][cg][node][ctx][0] + 128) >> 8) + vp5_ract_lc[ct][cg][node][ctx][1], 1, 254);
    return 0;
}