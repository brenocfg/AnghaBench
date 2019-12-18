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
struct TYPE_3__ {double* yule_coeff_a; double* yule_coeff_b; float* yule_hist_a; float* yule_hist_b; int yule_hist_i; } ;
typedef  TYPE_1__ ReplayGainContext ;

/* Variables and functions */
 int fabs (float) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void yule_filter_stereo_samples(ReplayGainContext *s, const float *src,
                                       float *dst, int nb_samples)
{
    const double *coeff_a = s->yule_coeff_a;
    const double *coeff_b = s->yule_coeff_b;
    float *hist_a   = s->yule_hist_a;
    float *hist_b   = s->yule_hist_b;
    double left, right;
    int i, j;

    i = s->yule_hist_i;

    // If filter history is very small magnitude, clear it completely to
    // prevent denormals from rattling around in there forever
    // (slowing us down).

    for (j = -20; j < 0; ++j)
        if (fabs(hist_a[i + j]) > 1e-10 || fabs(hist_b[i + j]) > 1e-10)
            break;

    if (!j) {
        memset(s->yule_hist_a, 0, sizeof(s->yule_hist_a));
        memset(s->yule_hist_b, 0, sizeof(s->yule_hist_b));
    }

    while (nb_samples--) {
        left   = (hist_b[i] = src[0]) * coeff_b[0];
        right  = (hist_b[i + 1] = src[1]) * coeff_b[0];
        left  += hist_b[i -  2] * coeff_b[ 1] - hist_a[i -  2] * coeff_a[1 ];
        right += hist_b[i -  1] * coeff_b[ 1] - hist_a[i -  1] * coeff_a[1 ];
        left  += hist_b[i -  4] * coeff_b[ 2] - hist_a[i -  4] * coeff_a[2 ];
        right += hist_b[i -  3] * coeff_b[ 2] - hist_a[i -  3] * coeff_a[2 ];
        left  += hist_b[i -  6] * coeff_b[ 3] - hist_a[i -  6] * coeff_a[3 ];
        right += hist_b[i -  5] * coeff_b[ 3] - hist_a[i -  5] * coeff_a[3 ];
        left  += hist_b[i -  8] * coeff_b[ 4] - hist_a[i -  8] * coeff_a[4 ];
        right += hist_b[i -  7] * coeff_b[ 4] - hist_a[i -  7] * coeff_a[4 ];
        left  += hist_b[i - 10] * coeff_b[ 5] - hist_a[i - 10] * coeff_a[5 ];
        right += hist_b[i -  9] * coeff_b[ 5] - hist_a[i -  9] * coeff_a[5 ];
        left  += hist_b[i - 12] * coeff_b[ 6] - hist_a[i - 12] * coeff_a[6 ];
        right += hist_b[i - 11] * coeff_b[ 6] - hist_a[i - 11] * coeff_a[6 ];
        left  += hist_b[i - 14] * coeff_b[ 7] - hist_a[i - 14] * coeff_a[7 ];
        right += hist_b[i - 13] * coeff_b[ 7] - hist_a[i - 13] * coeff_a[7 ];
        left  += hist_b[i - 16] * coeff_b[ 8] - hist_a[i - 16] * coeff_a[8 ];
        right += hist_b[i - 15] * coeff_b[ 8] - hist_a[i - 15] * coeff_a[8 ];
        left  += hist_b[i - 18] * coeff_b[ 9] - hist_a[i - 18] * coeff_a[9 ];
        right += hist_b[i - 17] * coeff_b[ 9] - hist_a[i - 17] * coeff_a[9 ];
        left  += hist_b[i - 20] * coeff_b[10] - hist_a[i - 20] * coeff_a[10];
        right += hist_b[i - 19] * coeff_b[10] - hist_a[i - 19] * coeff_a[10];
        dst[0] = hist_a[i    ] = (float)left;
        dst[1] = hist_a[i + 1] = (float)right;
        src += 2;
        dst += 2;

        if ((i += 2) == 256) {
            memcpy(hist_a, hist_a + 236, sizeof(*hist_a) * 20);
            memcpy(hist_b, hist_b + 236, sizeof(*hist_b) * 20);
            i = 20;
        }
    }

    s->yule_hist_i = i;
}