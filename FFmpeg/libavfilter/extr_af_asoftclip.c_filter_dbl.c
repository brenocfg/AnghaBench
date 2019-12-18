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
struct TYPE_3__ {double param; int type; } ;
typedef  TYPE_1__ ASoftClipContext ;

/* Variables and functions */
#define  ASC_ALG 134 
#define  ASC_ATAN 133 
#define  ASC_CUBIC 132 
#define  ASC_EXP 131 
#define  ASC_QUINTIC 130 
#define  ASC_SIN 129 
#define  ASC_TANH 128 
 double FFABS (double const) ; 
 double FFSIGN (double const) ; 
 int M_PI ; 
 double M_PI_2 ; 
 int atan (double const) ; 
 int /*<<< orphan*/  exp (int) ; 
 double pow (double const,int) ; 
 double sin (double const) ; 
 double const sqrt (double) ; 
 double tanh (double const) ; 

__attribute__((used)) static void filter_dbl(ASoftClipContext *s,
                       void **dptr, const void **sptr,
                       int nb_samples, int channels)
{
    double param = s->param;

    for (int c = 0; c < channels; c++) {
        const double *src = sptr[c];
        double *dst = dptr[c];

        switch (s->type) {
        case ASC_TANH:
            for (int n = 0; n < nb_samples; n++) {
                dst[n] = tanh(src[n] * param);
            }
            break;
        case ASC_ATAN:
            for (int n = 0; n < nb_samples; n++)
                dst[n] = 2. / M_PI * atan(src[n] * param);
            break;
        case ASC_CUBIC:
            for (int n = 0; n < nb_samples; n++) {
                if (FFABS(src[n]) >= 1.5)
                    dst[n] = FFSIGN(src[n]);
                else
                    dst[n] = src[n] - 0.1481 * pow(src[n], 3.);
            }
            break;
        case ASC_EXP:
            for (int n = 0; n < nb_samples; n++)
                dst[n] = 2. / (1. + exp(-2. * src[n])) - 1.;
            break;
        case ASC_ALG:
            for (int n = 0; n < nb_samples; n++)
                dst[n] = src[n] / (sqrt(param + src[n] * src[n]));
            break;
        case ASC_QUINTIC:
            for (int n = 0; n < nb_samples; n++) {
                if (FFABS(src[n]) >= 1.25)
                    dst[n] = FFSIGN(src[n]);
                else
                    dst[n] = src[n] - 0.08192 * pow(src[n], 5.);
            }
            break;
        case ASC_SIN:
            for (int n = 0; n < nb_samples; n++) {
                if (FFABS(src[n]) >= M_PI_2)
                    dst[n] = FFSIGN(src[n]);
                else
                    dst[n] = sin(src[n]);
            }
            break;
        }
    }
}