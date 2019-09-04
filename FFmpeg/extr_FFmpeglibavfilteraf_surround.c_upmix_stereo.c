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
struct TYPE_6__ {int /*<<< orphan*/  fr_y; int /*<<< orphan*/  fr_x; int /*<<< orphan*/  fl_y; int /*<<< orphan*/  fl_x; TYPE_1__* output; } ;
struct TYPE_5__ {scalar_t__* extended_data; } ;
typedef  TYPE_2__ AudioSurroundContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 float cosf (float) ; 
 float powf (float,int /*<<< orphan*/ ) ; 
 float sinf (float) ; 

__attribute__((used)) static void upmix_stereo(AVFilterContext *ctx,
                         float l_phase,
                         float r_phase,
                         float c_phase,
                         float mag_total,
                         float x, float y,
                         int n)
{
    AudioSurroundContext *s = ctx->priv;
    float l_mag, r_mag, *dstl, *dstr;

    dstl = (float *)s->output->extended_data[0];
    dstr = (float *)s->output->extended_data[1];

    l_mag = powf(.5f * ( x + 1.f), s->fl_x) * powf((y + 1.f) * .5f, s->fl_y) * mag_total;
    r_mag = powf(.5f * (-x + 1.f), s->fr_x) * powf((y + 1.f) * .5f, s->fr_y) * mag_total;

    dstl[2 * n    ] = l_mag * cosf(l_phase);
    dstl[2 * n + 1] = l_mag * sinf(l_phase);

    dstr[2 * n    ] = r_mag * cosf(r_phase);
    dstr[2 * n + 1] = r_mag * sinf(r_phase);
}