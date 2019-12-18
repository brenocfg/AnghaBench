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
struct TYPE_6__ {float h; } ;
struct TYPE_5__ {scalar_t__ display_scale; float w; scalar_t__ orientation; } ;
typedef  TYPE_1__ ShowVolumeContext ;
typedef  TYPE_2__ AVFilterLink ;

/* Variables and functions */
 scalar_t__ LINEAR ; 
 float av_clipf (double,int /*<<< orphan*/ ,int) ; 
 double log10 (float) ; 

__attribute__((used)) static inline int calc_max_draw(ShowVolumeContext *s, AVFilterLink *outlink, float max)
{
    float max_val;
    if (s->display_scale == LINEAR) {
        max_val = max;
    } else { /* log */
        max_val = av_clipf(0.21 * log10(max) + 1, 0, 1);
    }
    if (s->orientation) { /* vertical */
        return outlink->h - outlink->h * max_val;
    } else { /* horizontal */
        return s->w * max_val;
    }
}