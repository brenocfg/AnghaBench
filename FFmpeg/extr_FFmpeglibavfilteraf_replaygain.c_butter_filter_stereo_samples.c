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
struct TYPE_3__ {double* butter_coeff_a; double* butter_coeff_b; float* butter_hist_a; float* butter_hist_b; int butter_hist_i; } ;
typedef  TYPE_1__ ReplayGainContext ;

/* Variables and functions */
 int fabs (float) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void butter_filter_stereo_samples(ReplayGainContext *s,
                                         float *samples, int nb_samples)
{
    const double *coeff_a = s->butter_coeff_a;
    const double *coeff_b = s->butter_coeff_b;
    float *hist_a   = s->butter_hist_a;
    float *hist_b   = s->butter_hist_b;
    double left, right;
    int i, j;

    i = s->butter_hist_i;

    // If filter history is very small magnitude, clear it completely
    // to prevent denormals from rattling around in there forever
    // (slowing us down).

    for (j = -4; j < 0; ++j)
        if (fabs(hist_a[i + j]) > 1e-10 || fabs(hist_b[i + j]) > 1e-10)
            break;

    if (!j) {
        memset(s->butter_hist_a, 0, sizeof(s->butter_hist_a));
        memset(s->butter_hist_b, 0, sizeof(s->butter_hist_b));
    }

    while (nb_samples--) {
        left   = (hist_b[i    ] = samples[0]) * coeff_b[0];
        right  = (hist_b[i + 1] = samples[1]) * coeff_b[0];
        left  += hist_b[i - 2] * coeff_b[1] - hist_a[i - 2] * coeff_a[1];
        right += hist_b[i - 1] * coeff_b[1] - hist_a[i - 1] * coeff_a[1];
        left  += hist_b[i - 4] * coeff_b[2] - hist_a[i - 4] * coeff_a[2];
        right += hist_b[i - 3] * coeff_b[2] - hist_a[i - 3] * coeff_a[2];
        samples[0] = hist_a[i    ] = (float) left;
        samples[1] = hist_a[i + 1] = (float) right;
        samples += 2;

        if ((i += 2) == 256) {
            memcpy(hist_a, hist_a + 252, sizeof(*hist_a) * 4);
            memcpy(hist_b, hist_b + 252, sizeof(*hist_b) * 4);
            i = 4;
        }
    }

    s->butter_hist_i = i;
}