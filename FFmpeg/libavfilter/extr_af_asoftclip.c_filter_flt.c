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
struct TYPE_3__ {float param; int type; } ;
typedef  TYPE_1__ ASoftClipContext ;

/* Variables and functions */
#define  ASC_ALG 134 
#define  ASC_ATAN 133 
#define  ASC_CUBIC 132 
#define  ASC_EXP 131 
#define  ASC_QUINTIC 130 
#define  ASC_SIN 129 
#define  ASC_TANH 128 
 double FFABS (float const) ; 
 float FFSIGN (float const) ; 
 float M_PI ; 
 double M_PI_2 ; 
 float atanf (float const) ; 
 int /*<<< orphan*/  expf (float) ; 
 float powf (float const,float) ; 
 float sinf (float const) ; 
 float const sqrtf (float) ; 
 float tanhf (float const) ; 

__attribute__((used)) static void filter_flt(ASoftClipContext *s,
                       void **dptr, const void **sptr,
                       int nb_samples, int channels)
{
    float param = s->param;

    for (int c = 0; c < channels; c++) {
        const float *src = sptr[c];
        float *dst = dptr[c];

        switch (s->type) {
        case ASC_TANH:
            for (int n = 0; n < nb_samples; n++) {
                dst[n] = tanhf(src[n] * param);
            }
            break;
        case ASC_ATAN:
            for (int n = 0; n < nb_samples; n++)
                dst[n] = 2.f / M_PI * atanf(src[n] * param);
            break;
        case ASC_CUBIC:
            for (int n = 0; n < nb_samples; n++) {
                if (FFABS(src[n]) >= 1.5f)
                    dst[n] = FFSIGN(src[n]);
                else
                    dst[n] = src[n] - 0.1481f * powf(src[n], 3.f);
            }
            break;
        case ASC_EXP:
            for (int n = 0; n < nb_samples; n++)
                dst[n] = 2.f / (1.f + expf(-2.f * src[n])) - 1.;
            break;
        case ASC_ALG:
            for (int n = 0; n < nb_samples; n++)
                dst[n] = src[n] / (sqrtf(param + src[n] * src[n]));
            break;
        case ASC_QUINTIC:
            for (int n = 0; n < nb_samples; n++) {
                if (FFABS(src[n]) >= 1.25)
                    dst[n] = FFSIGN(src[n]);
                else
                    dst[n] = src[n] - 0.08192f * powf(src[n], 5.f);
            }
            break;
        case ASC_SIN:
            for (int n = 0; n < nb_samples; n++) {
                if (FFABS(src[n]) >= M_PI_2)
                    dst[n] = FFSIGN(src[n]);
                else
                    dst[n] = sinf(src[n]);
            }
            break;
        }
    }
}