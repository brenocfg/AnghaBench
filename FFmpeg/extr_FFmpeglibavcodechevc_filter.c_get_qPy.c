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
struct TYPE_7__ {int* qp_y_tab; TYPE_2__ ps; } ;
struct TYPE_5__ {int log2_min_cb_size; int min_cb_width; } ;
typedef  TYPE_3__ HEVCContext ;

/* Variables and functions */

__attribute__((used)) static int get_qPy(HEVCContext *s, int xC, int yC)
{
    int log2_min_cb_size  = s->ps.sps->log2_min_cb_size;
    int x                 = xC >> log2_min_cb_size;
    int y                 = yC >> log2_min_cb_size;
    return s->qp_y_tab[x + y * s->ps.sps->min_cb_width];
}