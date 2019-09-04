#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_5__* hrtf; int /*<<< orphan*/  fir; int /*<<< orphan*/  neighborhood; int /*<<< orphan*/  lookup; } ;
struct SOFAlizerContext {TYPE_3__ sofa; scalar_t__ interpolate; } ;
struct TYPE_8__ {float* values; } ;
struct TYPE_7__ {int elements; float* values; } ;
struct TYPE_11__ {int R; int N; TYPE_2__ DataIR; TYPE_1__ DataDelay; } ;
struct TYPE_10__ {struct SOFAlizerContext* priv; } ;
typedef  TYPE_4__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 float* mysofa_interpolate (TYPE_5__*,float*,int,int*,int /*<<< orphan*/ ,float*) ; 
 int mysofa_lookup (int /*<<< orphan*/ ,float*) ; 
 int* mysofa_neighborhood (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int getfilter_float(AVFilterContext *ctx, float x, float y, float z,
                           float *left, float *right,
                           float *delay_left, float *delay_right)
{
    struct SOFAlizerContext *s = ctx->priv;
    float c[3], delays[2];
    float *fl, *fr;
    int nearest;
    int *neighbors;
    float *res;

    c[0] = x, c[1] = y, c[2] = z;
    nearest = mysofa_lookup(s->sofa.lookup, c);
    if (nearest < 0)
        return AVERROR(EINVAL);

    if (s->interpolate) {
        neighbors = mysofa_neighborhood(s->sofa.neighborhood, nearest);
        res = mysofa_interpolate(s->sofa.hrtf, c,
                                 nearest, neighbors,
                                 s->sofa.fir, delays);
    } else {
        if (s->sofa.hrtf->DataDelay.elements > s->sofa.hrtf->R) {
            delays[0] = s->sofa.hrtf->DataDelay.values[nearest * s->sofa.hrtf->R];
            delays[1] = s->sofa.hrtf->DataDelay.values[nearest * s->sofa.hrtf->R + 1];
        } else {
            delays[0] = s->sofa.hrtf->DataDelay.values[0];
            delays[1] = s->sofa.hrtf->DataDelay.values[1];
        }
        res = s->sofa.hrtf->DataIR.values + nearest * s->sofa.hrtf->N * s->sofa.hrtf->R;
    }

    *delay_left  = delays[0];
    *delay_right = delays[1];

    fl = res;
    fr = res + s->sofa.hrtf->N;

    memcpy(left, fl, sizeof(float) * s->sofa.hrtf->N);
    memcpy(right, fr, sizeof(float) * s->sofa.hrtf->N);

    return 0;
}