#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nb_groups; void** idx; TYPE_1__* groups; } ;
struct TYPE_7__ {int /*<<< orphan*/  gb; int /*<<< orphan*/  avctx; } ;
struct TYPE_6__ {int nb_exponent; int exp_ofs; } ;
typedef  TYPE_1__ DBEGroup ;
typedef  TYPE_2__ DBEContext ;
typedef  TYPE_3__ DBEChannel ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void**,void**,int) ; 
 int /*<<< orphan*/  memset (void**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int parse_indices(DBEContext *s, DBEChannel *c)
{
    DBEGroup *p, *g;
    int i, j;

    for (i = 0, p = NULL, g = c->groups; i < c->nb_groups; i++, p = g, g++) {
        if (get_bits1(&s->gb)) {
            int start = get_bits(&s->gb, 6);

            if (start > g->nb_exponent) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid start index\n");
                return AVERROR_INVALIDDATA;
            }

            for (j = 0; j < start; j++)
                c->idx[g->exp_ofs + j] = 0;

            for (; j < g->nb_exponent; j++)
                c->idx[g->exp_ofs + j] = get_bits(&s->gb, 2);
        } else if (i && g->nb_exponent == p->nb_exponent) {
            memcpy(c->idx + g->exp_ofs,
                   c->idx + p->exp_ofs,
                   g->nb_exponent * sizeof(c->idx[0]));
        } else {
            memset(c->idx + g->exp_ofs, 0, g->nb_exponent * sizeof(c->idx[0]));
        }
    }

    return 0;
}