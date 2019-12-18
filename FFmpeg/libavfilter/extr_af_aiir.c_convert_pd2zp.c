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
struct TYPE_6__ {TYPE_1__* iir; } ;
struct TYPE_5__ {int* nb_ab; double** ab; } ;
typedef  TYPE_1__ IIRChannel ;
typedef  TYPE_2__ AudioIIRContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int M_PI ; 
 double cos (double) ; 
 double sin (double) ; 

__attribute__((used)) static void convert_pd2zp(AVFilterContext *ctx, int channels)
{
    AudioIIRContext *s = ctx->priv;
    int ch;

    for (ch = 0; ch < channels; ch++) {
        IIRChannel *iir = &s->iir[ch];
        int n;

        for (n = 0; n < iir->nb_ab[0]; n++) {
            double r = iir->ab[0][2*n];
            double angle = M_PI*iir->ab[0][2*n+1]/180.;

            iir->ab[0][2*n]   = r * cos(angle);
            iir->ab[0][2*n+1] = r * sin(angle);
        }

        for (n = 0; n < iir->nb_ab[1]; n++) {
            double r = iir->ab[1][2*n];
            double angle = M_PI*iir->ab[1][2*n+1]/180.;

            iir->ab[1][2*n]   = r * cos(angle);
            iir->ab[1][2*n+1] = r * sin(angle);
        }
    }
}