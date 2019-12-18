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
struct TYPE_5__ {int log2_min_pu_size; int min_pu_width; int min_pu_height; } ;
typedef  TYPE_3__ HEVCContext ;

/* Variables and functions */

__attribute__((used)) static int get_pcm(HEVCContext *s, int x, int y)
{
    int log2_min_pu_size = s->ps.sps->log2_min_pu_size;
    int x_pu, y_pu;

    if (x < 0 || y < 0)
        return 2;

    x_pu = x >> log2_min_pu_size;
    y_pu = y >> log2_min_pu_size;

    if (x_pu >= s->ps.sps->min_pu_width || y_pu >= s->ps.sps->min_pu_height)
        return 2;
    return s->is_pcm[y_pu * s->ps.sps->min_pu_width + x_pu];
}