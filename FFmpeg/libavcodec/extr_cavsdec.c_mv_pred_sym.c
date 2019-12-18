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
typedef  enum cavs_block { ____Placeholder_cavs_block } cavs_block ;
struct TYPE_6__ {int x; int y; int /*<<< orphan*/  dist; scalar_t__ ref; } ;
typedef  TYPE_1__ cavs_vector ;
struct TYPE_7__ {int sym_factor; int /*<<< orphan*/ * dist; } ;
typedef  TYPE_2__ AVSContext ;

/* Variables and functions */
 int MV_BWD_OFFS ; 
 int /*<<< orphan*/  set_mvs (TYPE_1__*,int) ; 

__attribute__((used)) static inline void mv_pred_sym(AVSContext *h, cavs_vector *src,
                               enum cavs_block size)
{
    cavs_vector *dst = src + MV_BWD_OFFS;

    /* backward mv is the scaled and negated forward mv */
    dst->x = -((src->x * h->sym_factor + 256) >> 9);
    dst->y = -((src->y * h->sym_factor + 256) >> 9);
    dst->ref = 0;
    dst->dist = h->dist[0];
    set_mvs(dst, size);
}