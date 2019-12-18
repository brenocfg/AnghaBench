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
struct TYPE_3__ {int filter_length; int phase_shift; int filter_type; int kaiser_beta; int /*<<< orphan*/  filter_bank; int /*<<< orphan*/  (* set_filter ) (int /*<<< orphan*/ ,double*,int,int) ;} ;
typedef  TYPE_1__ ResampleContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_RESAMPLE_FILTER_TYPE_BLACKMAN_NUTTALL 130 
#define  AV_RESAMPLE_FILTER_TYPE_CUBIC 129 
#define  AV_RESAMPLE_FILTER_TYPE_KAISER 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMAX (int,int /*<<< orphan*/ ) ; 
 double M_PI ; 
 int /*<<< orphan*/  av_free (double*) ; 
 double* av_malloc (int) ; 
 double bessel (int) ; 
 double cos (int) ; 
 double fabs (double) ; 
 double sin (double) ; 
 int sqrt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,double*,int,int) ; 

__attribute__((used)) static int build_filter(ResampleContext *c, double factor)
{
    int ph, i;
    double x, y, w;
    double *tab;
    int tap_count    = c->filter_length;
    int phase_count  = 1 << c->phase_shift;
    const int center = (tap_count - 1) / 2;

    tab = av_malloc(tap_count * sizeof(*tab));
    if (!tab)
        return AVERROR(ENOMEM);

    for (ph = 0; ph < phase_count; ph++) {
        double norm = 0;
        for (i = 0; i < tap_count; i++) {
            x = M_PI * ((double)(i - center) - (double)ph / phase_count) * factor;
            if (x == 0) y = 1.0;
            else        y = sin(x) / x;
            switch (c->filter_type) {
            case AV_RESAMPLE_FILTER_TYPE_CUBIC: {
                const float d = -0.5; //first order derivative = -0.5
                x = fabs(((double)(i - center) - (double)ph / phase_count) * factor);
                if (x < 1.0) y = 1 - 3 * x*x + 2 * x*x*x + d * (                -x*x + x*x*x);
                else         y =                           d * (-4 + 8 * x - 5 * x*x + x*x*x);
                break;
            }
            case AV_RESAMPLE_FILTER_TYPE_BLACKMAN_NUTTALL:
                w  = 2.0 * x / (factor * tap_count) + M_PI;
                y *= 0.3635819 - 0.4891775 * cos(    w) +
                                 0.1365995 * cos(2 * w) -
                                 0.0106411 * cos(3 * w);
                break;
            case AV_RESAMPLE_FILTER_TYPE_KAISER:
                w  = 2.0 * x / (factor * tap_count * M_PI);
                y *= bessel(c->kaiser_beta * sqrt(FFMAX(1 - w * w, 0)));
                break;
            }

            tab[i] = y;
            norm  += y;
        }
        /* normalize so that an uniform color remains the same */
        for (i = 0; i < tap_count; i++)
            tab[i] = tab[i] / norm;

        c->set_filter(c->filter_bank, tab, ph, tap_count);
    }

    av_free(tab);
    return 0;
}