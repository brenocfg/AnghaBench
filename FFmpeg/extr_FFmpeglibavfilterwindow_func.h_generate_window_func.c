#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 double FFABS (int) ; 
 float FFMIN (int,int) ; 
 int M_PI ; 
#define  WFUNC_BARTLETT 147 
#define  WFUNC_BHANN 146 
#define  WFUNC_BHARRIS 145 
#define  WFUNC_BLACKMAN 144 
#define  WFUNC_BNUTTALL 143 
#define  WFUNC_BOHMAN 142 
#define  WFUNC_CAUCHY 141 
#define  WFUNC_DOLPH 140 
#define  WFUNC_FLATTOP 139 
#define  WFUNC_GAUSS 138 
#define  WFUNC_HAMMING 137 
#define  WFUNC_HANNING 136 
#define  WFUNC_LANCZOS 135 
#define  WFUNC_NUTTALL 134 
#define  WFUNC_PARZEN 133 
#define  WFUNC_POISSON 132 
#define  WFUNC_RECT 131 
#define  WFUNC_SINE 130 
#define  WFUNC_TUKEY 129 
#define  WFUNC_WELCH 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 double cos (int) ; 
 double cosh (double) ; 
 float exp (int) ; 
 int fabs (double) ; 
 int powf (int,int) ; 
 int sin (int) ; 

__attribute__((used)) static inline void generate_window_func(float *lut, int N, int win_func,
                                        float *overlap)
{
    int n;

    switch (win_func) {
    case WFUNC_RECT:
        for (n = 0; n < N; n++)
            lut[n] = 1.;
        *overlap = 0.;
        break;
    case WFUNC_BARTLETT:
        for (n = 0; n < N; n++)
            lut[n] = 1.-fabs((n-(N-1)/2.)/((N-1)/2.));
        *overlap = 0.5;
        break;
    case WFUNC_HANNING:
        for (n = 0; n < N; n++)
            lut[n] = .5*(1-cos(2*M_PI*n/(N-1)));
        *overlap = 0.5;
        break;
    case WFUNC_HAMMING:
        for (n = 0; n < N; n++)
            lut[n] = .54-.46*cos(2*M_PI*n/(N-1));
        *overlap = 0.5;
        break;
    case WFUNC_BLACKMAN:
        for (n = 0; n < N; n++)
            lut[n] = .42659-.49656*cos(2*M_PI*n/(N-1))+.076849*cos(4*M_PI*n/(N-1));
        *overlap = 0.661;
        break;
    case WFUNC_WELCH:
        for (n = 0; n < N; n++)
            lut[n] = 1.-(n-(N-1)/2.)/((N-1)/2.)*(n-(N-1)/2.)/((N-1)/2.);
        *overlap = 0.293;
        break;
    case WFUNC_FLATTOP:
        for (n = 0; n < N; n++)
            lut[n] = 1.-1.985844164102*cos( 2*M_PI*n/(N-1))+1.791176438506*cos( 4*M_PI*n/(N-1))-
            1.282075284005*cos( 6*M_PI*n/(N-1))+0.667777530266*cos( 8*M_PI*n/(N-1))-
            0.240160796576*cos(10*M_PI*n/(N-1))+0.056656381764*cos(12*M_PI*n/(N-1))-
            0.008134974479*cos(14*M_PI*n/(N-1))+0.000624544650*cos(16*M_PI*n/(N-1))-
            0.000019808998*cos(18*M_PI*n/(N-1))+0.000000132974*cos(20*M_PI*n/(N-1));
        *overlap = 0.841;
        break;
    case WFUNC_BHARRIS:
        for (n = 0; n < N; n++)
            lut[n] = 0.35875-0.48829*cos(2*M_PI*n/(N-1))+0.14128*cos(4*M_PI*n/(N-1))-0.01168*cos(6*M_PI*n/(N-1));
        *overlap = 0.661;
        break;
    case WFUNC_BNUTTALL:
        for (n = 0; n < N; n++)
            lut[n] = 0.3635819-0.4891775*cos(2*M_PI*n/(N-1))+0.1365995*cos(4*M_PI*n/(N-1))-0.0106411*cos(6*M_PI*n/(N-1));
        *overlap = 0.661;
        break;
    case WFUNC_BHANN:
        for (n = 0; n < N; n++)
            lut[n] = 0.62-0.48*fabs(n/(double)(N-1)-.5)-0.38*cos(2*M_PI*n/(N-1));
        *overlap = 0.5;
        break;
    case WFUNC_SINE:
        for (n = 0; n < N; n++)
            lut[n] = sin(M_PI*n/(N-1));
        *overlap = 0.75;
        break;
    case WFUNC_NUTTALL:
        for (n = 0; n < N; n++)
            lut[n] = 0.355768-0.487396*cos(2*M_PI*n/(N-1))+0.144232*cos(4*M_PI*n/(N-1))-0.012604*cos(6*M_PI*n/(N-1));
        *overlap = 0.663;
        break;
    case WFUNC_LANCZOS:
        #define SINC(x) (!(x)) ? 1 : sin(M_PI * (x))/(M_PI * (x));
        for (n = 0; n < N; n++)
            lut[n] = SINC((2.*n)/(N-1)-1);
        *overlap = 0.75;
        break;
    case WFUNC_GAUSS:
        #define SQR(x) ((x)*(x))
        for (n = 0; n < N; n++)
            lut[n] = exp(-0.5 * SQR((n-(N-1)/2)/(0.4*(N-1)/2.f)));
        *overlap = 0.75;
        break;
    case WFUNC_TUKEY:
        for (n = 0; n < N; n++) {
            float M = (N-1)/2.;

            if (FFABS(n - M) >= 0.3 * M) {
                lut[n] = 0.5 * (1 + cos((M_PI*(FFABS(n - M) - 0.3 * M))/((1 - 0.3) * M)));
            } else {
                lut[n] = 1;
            }
        }
        *overlap = 0.33;
        break;
    case WFUNC_DOLPH: {
        double b = cosh(7.6009022095419887 / (N-1)), sum, t, c, norm = 0;
        int j;
        for (c = 1 - 1 / (b*b), n = (N-1) / 2; n >= 0; --n) {
            for (sum = !n, b = t = j = 1; j <= n && sum != t; b *= (n-j) * (1./j), ++j)
                t = sum, sum += (b *= c * (N - n - j) * (1./j));
            sum /= (N - 1 - n), sum /= (norm = norm ? norm : sum);
            lut[n] = sum;
            lut[N - 1 - n] = sum;
        }
        *overlap = 0.5;}
        break;
    case WFUNC_CAUCHY:
        for (n = 0; n < N; n++) {
            double x = 2 * ((n / (double)(N - 1)) - .5);

            if (x <= -.5 || x >= .5) {
                lut[n] = 0;
            } else {
                lut[n] = FFMIN(1, fabs(1/(1+4*16*x*x)));
            }
        }
        *overlap = 0.75;
        break;
    case WFUNC_PARZEN:
        for (n = 0; n < N; n++) {
            double x = 2 * ((n / (double)(N - 1)) - .5);

            if (x > 0.25 && x <= 0.5) {
                lut[n] = -2 * powf(-1 + 2 * x, 3);
            } else if (x >= -.5 && x < -.25) {
                lut[n] = 2 * powf(1 + 2 * x, 3);
            } else if (x >= -.25 && x < 0) {
                lut[n] = 1 - 24 * x * x - 48 * x * x * x;
            } else if (x >= 0 && x <= .25) {
                lut[n] = 1 - 24 * x * x + 48 * x * x * x;
            } else {
                lut[n] = 0;
            }
        }
        *overlap = 0.75;
        break;
    case WFUNC_POISSON:
        for (n = 0; n < N; n++) {
            double x = 2 * ((n / (double)(N - 1)) - .5);

            if (x >= 0 && x <= .5) {
                lut[n] = exp(-6*x);
            } else if (x < 0 && x >= -.5) {
                lut[n] = exp(6*x);
            } else {
                lut[n] = 0;
            }
        }
        *overlap = 0.75;
        break;
    case WFUNC_BOHMAN:
        for (n = 0; n < N; n++) {
            double x = 2 * ((n / (double)(N - 1))) - 1.;

            lut[n] = (1 - fabs(x)) * cos(M_PI*fabs(x)) + 1./M_PI*sin(M_PI*fabs(x));
        }
        *overlap = 0.75;
        break;
    default:
        av_assert0(0);
    }
}