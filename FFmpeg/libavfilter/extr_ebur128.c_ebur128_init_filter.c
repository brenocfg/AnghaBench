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
struct TYPE_5__ {TYPE_1__* d; scalar_t__ samplerate; } ;
struct TYPE_4__ {double* b; double* a; double** v; } ;
typedef  TYPE_2__ FFEBUR128State ;

/* Variables and functions */
 double M_PI ; 
 double pow (double,double) ; 
 double tan (double) ; 

__attribute__((used)) static void ebur128_init_filter(FFEBUR128State * st)
{
    int i, j;

    double f0 = 1681.974450955533;
    double G = 3.999843853973347;
    double Q = 0.7071752369554196;

    double K = tan(M_PI * f0 / (double) st->samplerate);
    double Vh = pow(10.0, G / 20.0);
    double Vb = pow(Vh, 0.4996667741545416);

    double pb[3] = { 0.0, 0.0, 0.0 };
    double pa[3] = { 1.0, 0.0, 0.0 };
    double rb[3] = { 1.0, -2.0, 1.0 };
    double ra[3] = { 1.0, 0.0, 0.0 };

    double a0 = 1.0 + K / Q + K * K;
    pb[0] = (Vh + Vb * K / Q + K * K) / a0;
    pb[1] = 2.0 * (K * K - Vh) / a0;
    pb[2] = (Vh - Vb * K / Q + K * K) / a0;
    pa[1] = 2.0 * (K * K - 1.0) / a0;
    pa[2] = (1.0 - K / Q + K * K) / a0;

    f0 = 38.13547087602444;
    Q = 0.5003270373238773;
    K = tan(M_PI * f0 / (double) st->samplerate);

    ra[1] = 2.0 * (K * K - 1.0) / (1.0 + K / Q + K * K);
    ra[2] = (1.0 - K / Q + K * K) / (1.0 + K / Q + K * K);

    st->d->b[0] = pb[0] * rb[0];
    st->d->b[1] = pb[0] * rb[1] + pb[1] * rb[0];
    st->d->b[2] = pb[0] * rb[2] + pb[1] * rb[1] + pb[2] * rb[0];
    st->d->b[3] = pb[1] * rb[2] + pb[2] * rb[1];
    st->d->b[4] = pb[2] * rb[2];

    st->d->a[0] = pa[0] * ra[0];
    st->d->a[1] = pa[0] * ra[1] + pa[1] * ra[0];
    st->d->a[2] = pa[0] * ra[2] + pa[1] * ra[1] + pa[2] * ra[0];
    st->d->a[3] = pa[1] * ra[2] + pa[2] * ra[1];
    st->d->a[4] = pa[2] * ra[2];

    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 5; ++j) {
            st->d->v[i][j] = 0.0;
        }
    }
}