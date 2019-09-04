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
struct TYPE_4__ {int*** mb_types_stats; int*** mb_type; } ;
typedef  TYPE_1__ VP56Model ;
struct TYPE_5__ {TYPE_1__* modelp; int /*<<< orphan*/  c; } ;
typedef  TYPE_2__ VP56Context ;

/* Variables and functions */
 int /*<<< orphan*/  ff_vp56_mb_type_model_model ; 
 int /*<<< orphan*/  ff_vp56_pmbtm_tree ; 
 int /*<<< orphan*/ ** ff_vp56_pre_def_mb_type_stats ; 
 int /*<<< orphan*/  memcpy (int**,int /*<<< orphan*/ ,int) ; 
 int vp56_rac_get (int /*<<< orphan*/ *) ; 
 scalar_t__ vp56_rac_get_prob_branchy (int /*<<< orphan*/ *,int) ; 
 int vp56_rac_get_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vp56_rac_gets (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void vp56_parse_mb_type_models(VP56Context *s)
{
    VP56RangeCoder *c = &s->c;
    VP56Model *model = s->modelp;
    int i, ctx, type;

    for (ctx=0; ctx<3; ctx++) {
        if (vp56_rac_get_prob_branchy(c, 174)) {
            int idx = vp56_rac_gets(c, 4);
            memcpy(model->mb_types_stats[ctx],
                   ff_vp56_pre_def_mb_type_stats[idx][ctx],
                   sizeof(model->mb_types_stats[ctx]));
        }
        if (vp56_rac_get_prob_branchy(c, 254)) {
            for (type=0; type<10; type++) {
                for(i=0; i<2; i++) {
                    if (vp56_rac_get_prob_branchy(c, 205)) {
                        int delta, sign = vp56_rac_get(c);

                        delta = vp56_rac_get_tree(c, ff_vp56_pmbtm_tree,
                                                  ff_vp56_mb_type_model_model);
                        if (!delta)
                            delta = 4 * vp56_rac_gets(c, 7);
                        model->mb_types_stats[ctx][type][i] += (delta ^ -sign) + sign;
                    }
                }
            }
        }
    }

    /* compute MB type probability tables based on previous MB type */
    for (ctx=0; ctx<3; ctx++) {
        int p[10];

        for (type=0; type<10; type++)
            p[type] = 100 * model->mb_types_stats[ctx][type][1];

        for (type=0; type<10; type++) {
            int p02, p34, p0234, p17, p56, p89, p5689, p156789;

            /* conservative MB type probability */
            model->mb_type[ctx][type][0] = 255 - (255 * model->mb_types_stats[ctx][type][0]) / (1 + model->mb_types_stats[ctx][type][0] + model->mb_types_stats[ctx][type][1]);

            p[type] = 0;    /* same MB type => weight is null */

            /* binary tree parsing probabilities */
            p02 = p[0] + p[2];
            p34 = p[3] + p[4];
            p0234 = p02 + p34;
            p17 = p[1] + p[7];
            p56 = p[5] + p[6];
            p89 = p[8] + p[9];
            p5689 = p56 + p89;
            p156789 = p17 + p5689;

            model->mb_type[ctx][type][1] = 1 + 255 * p0234/(1+p0234+p156789);
            model->mb_type[ctx][type][2] = 1 + 255 * p02  / (1+p0234);
            model->mb_type[ctx][type][3] = 1 + 255 * p17  / (1+p156789);
            model->mb_type[ctx][type][4] = 1 + 255 * p[0] / (1+p02);
            model->mb_type[ctx][type][5] = 1 + 255 * p[3] / (1+p34);
            model->mb_type[ctx][type][6] = 1 + 255 * p[1] / (1+p17);
            model->mb_type[ctx][type][7] = 1 + 255 * p56  / (1+p5689);
            model->mb_type[ctx][type][8] = 1 + 255 * p[5] / (1+p56);
            model->mb_type[ctx][type][9] = 1 + 255 * p[8] / (1+p89);

            /* restore initial value */
            p[type] = 100 * model->mb_types_stats[ctx][type][1];
        }
    }
}