#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flength; float* prev_stereo_weights; float* stereo_weights; size_t bandwidth; TYPE_1__* frame; } ;
struct TYPE_4__ {int output; } ;
typedef  TYPE_2__ SilkContext ;

/* Variables and functions */
 int SILK_HISTORY ; 
 float av_clipf (int,double,double) ; 
 int* ff_silk_stereo_interp_len ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 

__attribute__((used)) static void silk_unmix_ms(SilkContext *s, float *l, float *r)
{
    float *mid    = s->frame[0].output + SILK_HISTORY - s->flength;
    float *side   = s->frame[1].output + SILK_HISTORY - s->flength;
    float w0_prev = s->prev_stereo_weights[0];
    float w1_prev = s->prev_stereo_weights[1];
    float w0      = s->stereo_weights[0];
    float w1      = s->stereo_weights[1];
    int n1        = ff_silk_stereo_interp_len[s->bandwidth];
    int i;

    for (i = 0; i < n1; i++) {
        float interp0 = w0_prev + i * (w0 - w0_prev) / n1;
        float interp1 = w1_prev + i * (w1 - w1_prev) / n1;
        float p0      = 0.25 * (mid[i - 2] + 2 * mid[i - 1] + mid[i]);

        l[i] = av_clipf((1 + interp1) * mid[i - 1] + side[i - 1] + interp0 * p0, -1.0, 1.0);
        r[i] = av_clipf((1 - interp1) * mid[i - 1] - side[i - 1] - interp0 * p0, -1.0, 1.0);
    }

    for (; i < s->flength; i++) {
        float p0 = 0.25 * (mid[i - 2] + 2 * mid[i - 1] + mid[i]);

        l[i] = av_clipf((1 + w1) * mid[i - 1] + side[i - 1] + w0 * p0, -1.0, 1.0);
        r[i] = av_clipf((1 - w1) * mid[i - 1] - side[i - 1] - w0 * p0, -1.0, 1.0);
    }

    memcpy(s->prev_stereo_weights, s->stereo_weights, sizeof(s->stereo_weights));
}