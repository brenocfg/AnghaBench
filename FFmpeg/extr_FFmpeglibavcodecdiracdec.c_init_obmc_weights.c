#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int blheight; int /*<<< orphan*/ * obmc_weight; } ;
typedef  int /*<<< orphan*/  Plane ;
typedef  TYPE_1__ DiracContext ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_BLOCKSIZE ; 
 int /*<<< orphan*/  init_obmc_weight (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void init_obmc_weights(DiracContext *s, Plane *p, int by)
{
    int top = !by;
    int bottom = by == s->blheight-1;

    /* don't bother re-initing for rows 2 to blheight-2, the weights don't change */
    if (top || bottom || by == 1) {
        init_obmc_weight(p, s->obmc_weight[0], MAX_BLOCKSIZE, 1, 0, top, bottom);
        init_obmc_weight(p, s->obmc_weight[1], MAX_BLOCKSIZE, 0, 0, top, bottom);
        init_obmc_weight(p, s->obmc_weight[2], MAX_BLOCKSIZE, 0, 1, top, bottom);
    }
}