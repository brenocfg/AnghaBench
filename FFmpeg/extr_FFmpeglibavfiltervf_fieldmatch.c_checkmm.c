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
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int combpel; int /*<<< orphan*/  nxt; int /*<<< orphan*/  src; int /*<<< orphan*/  prv; } ;
typedef  TYPE_1__ FieldMatchContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int abs (int) ; 
 int calc_combed_score (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_weave_frame (TYPE_2__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkmm(AVFilterContext *ctx, int *combs, int m1, int m2,
                   AVFrame **gen_frames, int field)
{
    const FieldMatchContext *fm = ctx->priv;

#define LOAD_COMB(mid) do {                                                     \
    if (combs[mid] < 0) {                                                       \
        if (!gen_frames[mid])                                                   \
            gen_frames[mid] = create_weave_frame(ctx, mid, field,               \
                                                 fm->prv, fm->src, fm->nxt);    \
        combs[mid] = calc_combed_score(fm, gen_frames[mid]);                    \
    }                                                                           \
} while (0)

    LOAD_COMB(m1);
    LOAD_COMB(m2);

    if ((combs[m2] * 3 < combs[m1] || (combs[m2] * 2 < combs[m1] && combs[m1] > fm->combpel)) &&
        abs(combs[m2] - combs[m1]) >= 30 && combs[m2] < fm->combpel)
        return m2;
    else
        return m1;
}