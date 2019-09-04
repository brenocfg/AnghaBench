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
struct TYPE_6__ {TYPE_1__* sps; } ;
struct TYPE_7__ {int* is_pcm; TYPE_2__ ps; } ;
struct TYPE_5__ {int log2_min_pu_size; int min_pu_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_3__ HEVCContext ;

/* Variables and functions */
 int FFMIN (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_deblocking_bypass(HEVCContext *s, int x0, int y0, int log2_cb_size)
{
    int cb_size          = 1 << log2_cb_size;
    int log2_min_pu_size = s->ps.sps->log2_min_pu_size;

    int min_pu_width     = s->ps.sps->min_pu_width;
    int x_end = FFMIN(x0 + cb_size, s->ps.sps->width);
    int y_end = FFMIN(y0 + cb_size, s->ps.sps->height);
    int i, j;

    for (j = (y0 >> log2_min_pu_size); j < (y_end >> log2_min_pu_size); j++)
        for (i = (x0 >> log2_min_pu_size); i < (x_end >> log2_min_pu_size); i++)
            s->is_pcm[i + j * min_pu_width] = 2;
}