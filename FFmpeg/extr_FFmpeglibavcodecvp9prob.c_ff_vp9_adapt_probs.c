#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_18__ {size_t framectxid; scalar_t__ comppredmode; scalar_t__ txfmmode; scalar_t__ filtermode; scalar_t__ highprecisionmvs; scalar_t__ intraonly; scalar_t__ keyframe; } ;
struct TYPE_19__ {TYPE_4__ h; } ;
struct TYPE_16__ {int /*<<< orphan*/  tx8p; int /*<<< orphan*/  tx16p; int /*<<< orphan*/  tx32p; int /*<<< orphan*/  skip; } ;
struct TYPE_17__ {TYPE_2__ p; } ;
struct TYPE_13__ {TYPE_9__* td; TYPE_5__ s; TYPE_3__ prob; TYPE_1__* prob_ctx; int /*<<< orphan*/  last_keyframe; } ;
typedef  TYPE_10__ VP9Context ;
struct TYPE_22__ {unsigned int****** eob; unsigned int****** coef; unsigned int** skip; unsigned int** intra; unsigned int** comp; unsigned int** comp_ref; unsigned int*** single_ref; unsigned int*** partition; unsigned int** tx16p; unsigned int** tx32p; unsigned int** tx8p; unsigned int** filter; unsigned int** mv_mode; unsigned int* mv_joint; unsigned int** y_mode; unsigned int** uv_mode; TYPE_7__* mv_comp; } ;
struct TYPE_23__ {TYPE_8__ counts; } ;
struct TYPE_21__ {unsigned int* sign; unsigned int* classes; unsigned int* class0; unsigned int** bits; unsigned int** class0_fp; unsigned int* fp; unsigned int* class0_hp; unsigned int* hp; } ;
struct TYPE_20__ {int /*<<< orphan*/  hp; int /*<<< orphan*/  class0_hp; int /*<<< orphan*/ * fp; int /*<<< orphan*/ ** class0_fp; int /*<<< orphan*/ * bits; int /*<<< orphan*/  class0; int /*<<< orphan*/ * classes; int /*<<< orphan*/  sign; } ;
struct TYPE_14__ {int /*<<< orphan*/ ** uv_mode; int /*<<< orphan*/ ** y_mode; TYPE_6__* mv_comp; int /*<<< orphan*/ * mv_joint; int /*<<< orphan*/ ** mv_mode; int /*<<< orphan*/ ** filter; int /*<<< orphan*/ ** tx32p; int /*<<< orphan*/ ** tx16p; int /*<<< orphan*/ * tx8p; int /*<<< orphan*/ *** partition; int /*<<< orphan*/ ** single_ref; int /*<<< orphan*/ * comp_ref; int /*<<< orphan*/ * comp; int /*<<< orphan*/ * intra; int /*<<< orphan*/ * skip; } ;
struct TYPE_15__ {int /*<<< orphan*/ ****** coef; TYPE_11__ p; } ;
typedef  TYPE_11__ ProbContext ;

/* Variables and functions */
 size_t DC_PRED ; 
 size_t DIAG_DOWN_LEFT_PRED ; 
 size_t DIAG_DOWN_RIGHT_PRED ; 
 scalar_t__ FILTER_SWITCHABLE ; 
 size_t HOR_DOWN_PRED ; 
 size_t HOR_PRED ; 
 size_t HOR_UP_PRED ; 
 scalar_t__ PRED_COMPREF ; 
 scalar_t__ PRED_SINGLEREF ; 
 scalar_t__ PRED_SWITCHABLE ; 
 size_t TM_VP8_PRED ; 
 scalar_t__ TX_SWITCHABLE ; 
 size_t VERT_LEFT_PRED ; 
 size_t VERT_PRED ; 
 size_t VERT_RIGHT_PRED ; 
 int /*<<< orphan*/  adapt_prob (int /*<<< orphan*/ *,unsigned int,unsigned int,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void ff_vp9_adapt_probs(VP9Context *s)
{
    int i, j, k, l, m;
    ProbContext *p = &s->prob_ctx[s->s.h.framectxid].p;
    int uf = (s->s.h.keyframe || s->s.h.intraonly || !s->last_keyframe) ? 112 : 128;

    // coefficients
    for (i = 0; i < 4; i++)
        for (j = 0; j < 2; j++)
            for (k = 0; k < 2; k++)
                for (l = 0; l < 6; l++)
                    for (m = 0; m < 6; m++) {
                        uint8_t *pp = s->prob_ctx[s->s.h.framectxid].coef[i][j][k][l][m];
                        unsigned *e = s->td[0].counts.eob[i][j][k][l][m];
                        unsigned *c = s->td[0].counts.coef[i][j][k][l][m];

                        if (l == 0 && m >= 3) // dc only has 3 pt
                            break;

                        adapt_prob(&pp[0], e[0], e[1], 24, uf);
                        adapt_prob(&pp[1], c[0], c[1] + c[2], 24, uf);
                        adapt_prob(&pp[2], c[1], c[2], 24, uf);
                    }

    if (s->s.h.keyframe || s->s.h.intraonly) {
        memcpy(p->skip,  s->prob.p.skip,  sizeof(p->skip));
        memcpy(p->tx32p, s->prob.p.tx32p, sizeof(p->tx32p));
        memcpy(p->tx16p, s->prob.p.tx16p, sizeof(p->tx16p));
        memcpy(p->tx8p,  s->prob.p.tx8p,  sizeof(p->tx8p));
        return;
    }

    // skip flag
    for (i = 0; i < 3; i++)
        adapt_prob(&p->skip[i], s->td[0].counts.skip[i][0],
                   s->td[0].counts.skip[i][1], 20, 128);

    // intra/inter flag
    for (i = 0; i < 4; i++)
        adapt_prob(&p->intra[i], s->td[0].counts.intra[i][0],
                   s->td[0].counts.intra[i][1], 20, 128);

    // comppred flag
    if (s->s.h.comppredmode == PRED_SWITCHABLE) {
        for (i = 0; i < 5; i++)
            adapt_prob(&p->comp[i], s->td[0].counts.comp[i][0],
                       s->td[0].counts.comp[i][1], 20, 128);
    }

    // reference frames
    if (s->s.h.comppredmode != PRED_SINGLEREF) {
        for (i = 0; i < 5; i++)
            adapt_prob(&p->comp_ref[i], s->td[0].counts.comp_ref[i][0],
                       s->td[0].counts.comp_ref[i][1], 20, 128);
    }

    if (s->s.h.comppredmode != PRED_COMPREF) {
        for (i = 0; i < 5; i++) {
            uint8_t *pp = p->single_ref[i];
            unsigned (*c)[2] = s->td[0].counts.single_ref[i];

            adapt_prob(&pp[0], c[0][0], c[0][1], 20, 128);
            adapt_prob(&pp[1], c[1][0], c[1][1], 20, 128);
        }
    }

    // block partitioning
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++) {
            uint8_t *pp = p->partition[i][j];
            unsigned *c = s->td[0].counts.partition[i][j];

            adapt_prob(&pp[0], c[0], c[1] + c[2] + c[3], 20, 128);
            adapt_prob(&pp[1], c[1], c[2] + c[3], 20, 128);
            adapt_prob(&pp[2], c[2], c[3], 20, 128);
        }

    // tx size
    if (s->s.h.txfmmode == TX_SWITCHABLE) {
        for (i = 0; i < 2; i++) {
            unsigned *c16 = s->td[0].counts.tx16p[i], *c32 = s->td[0].counts.tx32p[i];

            adapt_prob(&p->tx8p[i], s->td[0].counts.tx8p[i][0],
                       s->td[0].counts.tx8p[i][1], 20, 128);
            adapt_prob(&p->tx16p[i][0], c16[0], c16[1] + c16[2], 20, 128);
            adapt_prob(&p->tx16p[i][1], c16[1], c16[2], 20, 128);
            adapt_prob(&p->tx32p[i][0], c32[0], c32[1] + c32[2] + c32[3], 20, 128);
            adapt_prob(&p->tx32p[i][1], c32[1], c32[2] + c32[3], 20, 128);
            adapt_prob(&p->tx32p[i][2], c32[2], c32[3], 20, 128);
        }
    }

    // interpolation filter
    if (s->s.h.filtermode == FILTER_SWITCHABLE) {
        for (i = 0; i < 4; i++) {
            uint8_t *pp = p->filter[i];
            unsigned *c = s->td[0].counts.filter[i];

            adapt_prob(&pp[0], c[0], c[1] + c[2], 20, 128);
            adapt_prob(&pp[1], c[1], c[2], 20, 128);
        }
    }

    // inter modes
    for (i = 0; i < 7; i++) {
        uint8_t *pp = p->mv_mode[i];
        unsigned *c = s->td[0].counts.mv_mode[i];

        adapt_prob(&pp[0], c[2], c[1] + c[0] + c[3], 20, 128);
        adapt_prob(&pp[1], c[0], c[1] + c[3], 20, 128);
        adapt_prob(&pp[2], c[1], c[3], 20, 128);
    }

    // mv joints
    {
        uint8_t *pp = p->mv_joint;
        unsigned *c = s->td[0].counts.mv_joint;

        adapt_prob(&pp[0], c[0], c[1] + c[2] + c[3], 20, 128);
        adapt_prob(&pp[1], c[1], c[2] + c[3], 20, 128);
        adapt_prob(&pp[2], c[2], c[3], 20, 128);
    }

    // mv components
    for (i = 0; i < 2; i++) {
        uint8_t *pp;
        unsigned *c, (*c2)[2], sum;

        adapt_prob(&p->mv_comp[i].sign, s->td[0].counts.mv_comp[i].sign[0],
                   s->td[0].counts.mv_comp[i].sign[1], 20, 128);

        pp  = p->mv_comp[i].classes;
        c   = s->td[0].counts.mv_comp[i].classes;
        sum = c[1] + c[2] + c[3] + c[4] + c[5] +
              c[6] + c[7] + c[8] + c[9] + c[10];
        adapt_prob(&pp[0], c[0], sum, 20, 128);
        sum -= c[1];
        adapt_prob(&pp[1], c[1], sum, 20, 128);
        sum -= c[2] + c[3];
        adapt_prob(&pp[2], c[2] + c[3], sum, 20, 128);
        adapt_prob(&pp[3], c[2], c[3], 20, 128);
        sum -= c[4] + c[5];
        adapt_prob(&pp[4], c[4] + c[5], sum, 20, 128);
        adapt_prob(&pp[5], c[4], c[5], 20, 128);
        sum -= c[6];
        adapt_prob(&pp[6], c[6], sum, 20, 128);
        adapt_prob(&pp[7], c[7] + c[8], c[9] + c[10], 20, 128);
        adapt_prob(&pp[8], c[7], c[8], 20, 128);
        adapt_prob(&pp[9], c[9], c[10], 20, 128);

        adapt_prob(&p->mv_comp[i].class0, s->td[0].counts.mv_comp[i].class0[0],
                   s->td[0].counts.mv_comp[i].class0[1], 20, 128);
        pp = p->mv_comp[i].bits;
        c2 = s->td[0].counts.mv_comp[i].bits;
        for (j = 0; j < 10; j++)
            adapt_prob(&pp[j], c2[j][0], c2[j][1], 20, 128);

        for (j = 0; j < 2; j++) {
            pp = p->mv_comp[i].class0_fp[j];
            c  = s->td[0].counts.mv_comp[i].class0_fp[j];
            adapt_prob(&pp[0], c[0], c[1] + c[2] + c[3], 20, 128);
            adapt_prob(&pp[1], c[1], c[2] + c[3], 20, 128);
            adapt_prob(&pp[2], c[2], c[3], 20, 128);
        }
        pp = p->mv_comp[i].fp;
        c  = s->td[0].counts.mv_comp[i].fp;
        adapt_prob(&pp[0], c[0], c[1] + c[2] + c[3], 20, 128);
        adapt_prob(&pp[1], c[1], c[2] + c[3], 20, 128);
        adapt_prob(&pp[2], c[2], c[3], 20, 128);

        if (s->s.h.highprecisionmvs) {
            adapt_prob(&p->mv_comp[i].class0_hp,
                       s->td[0].counts.mv_comp[i].class0_hp[0],
                       s->td[0].counts.mv_comp[i].class0_hp[1], 20, 128);
            adapt_prob(&p->mv_comp[i].hp, s->td[0].counts.mv_comp[i].hp[0],
                       s->td[0].counts.mv_comp[i].hp[1], 20, 128);
        }
    }

    // y intra modes
    for (i = 0; i < 4; i++) {
        uint8_t *pp = p->y_mode[i];
        unsigned *c = s->td[0].counts.y_mode[i], sum, s2;

        sum = c[0] + c[1] + c[3] + c[4] + c[5] + c[6] + c[7] + c[8] + c[9];
        adapt_prob(&pp[0], c[DC_PRED], sum, 20, 128);
        sum -= c[TM_VP8_PRED];
        adapt_prob(&pp[1], c[TM_VP8_PRED], sum, 20, 128);
        sum -= c[VERT_PRED];
        adapt_prob(&pp[2], c[VERT_PRED], sum, 20, 128);
        s2   = c[HOR_PRED] + c[DIAG_DOWN_RIGHT_PRED] + c[VERT_RIGHT_PRED];
        sum -= s2;
        adapt_prob(&pp[3], s2, sum, 20, 128);
        s2 -= c[HOR_PRED];
        adapt_prob(&pp[4], c[HOR_PRED], s2, 20, 128);
        adapt_prob(&pp[5], c[DIAG_DOWN_RIGHT_PRED], c[VERT_RIGHT_PRED],
                   20, 128);
        sum -= c[DIAG_DOWN_LEFT_PRED];
        adapt_prob(&pp[6], c[DIAG_DOWN_LEFT_PRED], sum, 20, 128);
        sum -= c[VERT_LEFT_PRED];
        adapt_prob(&pp[7], c[VERT_LEFT_PRED], sum, 20, 128);
        adapt_prob(&pp[8], c[HOR_DOWN_PRED], c[HOR_UP_PRED], 20, 128);
    }

    // uv intra modes
    for (i = 0; i < 10; i++) {
        uint8_t *pp = p->uv_mode[i];
        unsigned *c = s->td[0].counts.uv_mode[i], sum, s2;

        sum = c[0] + c[1] + c[3] + c[4] + c[5] + c[6] + c[7] + c[8] + c[9];
        adapt_prob(&pp[0], c[DC_PRED], sum, 20, 128);
        sum -= c[TM_VP8_PRED];
        adapt_prob(&pp[1], c[TM_VP8_PRED], sum, 20, 128);
        sum -= c[VERT_PRED];
        adapt_prob(&pp[2], c[VERT_PRED], sum, 20, 128);
        s2   = c[HOR_PRED] + c[DIAG_DOWN_RIGHT_PRED] + c[VERT_RIGHT_PRED];
        sum -= s2;
        adapt_prob(&pp[3], s2, sum, 20, 128);
        s2 -= c[HOR_PRED];
        adapt_prob(&pp[4], c[HOR_PRED], s2, 20, 128);
        adapt_prob(&pp[5], c[DIAG_DOWN_RIGHT_PRED], c[VERT_RIGHT_PRED],
                   20, 128);
        sum -= c[DIAG_DOWN_LEFT_PRED];
        adapt_prob(&pp[6], c[DIAG_DOWN_LEFT_PRED], sum, 20, 128);
        sum -= c[VERT_LEFT_PRED];
        adapt_prob(&pp[7], c[VERT_LEFT_PRED], sum, 20, 128);
        adapt_prob(&pp[8], c[HOR_DOWN_PRED], c[HOR_UP_PRED], 20, 128);
    }
}