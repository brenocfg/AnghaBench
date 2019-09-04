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
struct TYPE_7__ {TYPE_2__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  fc_y; int /*<<< orphan*/  fc_x; TYPE_1__* output; } ;
struct TYPE_5__ {scalar_t__* extended_data; } ;
typedef  TYPE_2__ AudioSurroundContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 float cosf (float) ; 
 float fabsf (float) ; 
 float powf (float,int /*<<< orphan*/ ) ; 
 float sinf (float) ; 

__attribute__((used)) static void upmix_1_0(AVFilterContext *ctx,
                      float l_phase,
                      float r_phase,
                      float c_phase,
                      float mag_total,
                      float x, float y,
                      int n)
{
    AudioSurroundContext *s = ctx->priv;
    float mag, *dst;

    dst = (float *)s->output->extended_data[0];

    mag = powf(1.f - fabsf(x), s->fc_x) * powf((y + 1.f) * .5f, s->fc_y) * mag_total;

    dst[2 * n    ] = mag * cosf(c_phase);
    dst[2 * n + 1] = mag * sinf(c_phase);
}