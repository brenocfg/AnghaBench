#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int blwidth; int /*<<< orphan*/ * obmc_weight; TYPE_1__* plane; } ;
struct TYPE_5__ {int xbsep; int xoffset; } ;
typedef  TYPE_1__ Plane ;
typedef  TYPE_2__ DiracContext ;
typedef  int /*<<< orphan*/  DiracBlock ;

/* Variables and functions */
 int /*<<< orphan*/  block_mc (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void mc_row(DiracContext *s, DiracBlock *block, uint16_t *mctmp, int plane, int dsty)
{
    Plane *p = &s->plane[plane];
    int x, dstx = p->xbsep - p->xoffset;

    block_mc(s, block, mctmp, s->obmc_weight[0], plane, -p->xoffset, dsty);
    mctmp += p->xbsep;

    for (x = 1; x < s->blwidth-1; x++) {
        block_mc(s, block+x, mctmp, s->obmc_weight[1], plane, dstx, dsty);
        dstx  += p->xbsep;
        mctmp += p->xbsep;
    }
    block_mc(s, block+x, mctmp, s->obmc_weight[2], plane, dstx, dsty);
}