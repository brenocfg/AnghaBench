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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int format; } ;
typedef  TYPE_1__ ResampleContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_SAMPLE_FMT_DBLP 134 
#define  AV_SAMPLE_FMT_FLTP 133 
#define  AV_SAMPLE_FMT_S16P 132 
#define  AV_SAMPLE_FMT_S32P 131 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FFMAX (int,int /*<<< orphan*/ ) ; 
 int M_PI ; 
#define  SWR_FILTER_TYPE_BLACKMAN_NUTTALL 130 
#define  SWR_FILTER_TYPE_CUBIC 129 
#define  SWR_FILTER_TYPE_KAISER 128 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_clip_int16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_clipl_int32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (double*) ; 
 double* av_malloc_array (int,int) ; 
 double bessel (double) ; 
 double cos (double) ; 
 double fabs (double) ; 
 int /*<<< orphan*/  llrint (double) ; 
 int /*<<< orphan*/  lrintf (double) ; 
 double sin (double) ; 
 double sqrt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_filter(ResampleContext *c, void *filter, double factor, int tap_count, int alloc, int phase_count, int scale,
                        int filter_type, double kaiser_beta){
    int ph, i;
    int ph_nb = phase_count % 2 ? phase_count : phase_count / 2 + 1;
    double x, y, w, t, s;
    double *tab = av_malloc_array(tap_count+1,  sizeof(*tab));
    double *sin_lut = av_malloc_array(ph_nb, sizeof(*sin_lut));
    const int center= (tap_count-1)/2;
    double norm = 0;
    int ret = AVERROR(ENOMEM);

    if (!tab || !sin_lut)
        goto fail;

    av_assert0(tap_count == 1 || tap_count % 2 == 0);

    /* if upsampling, only need to interpolate, no filter */
    if (factor > 1.0)
        factor = 1.0;

    if (factor == 1.0) {
        for (ph = 0; ph < ph_nb; ph++)
            sin_lut[ph] = sin(M_PI * ph / phase_count) * (center & 1 ? 1 : -1);
    }
    for(ph = 0; ph < ph_nb; ph++) {
        s = sin_lut[ph];
        for(i=0;i<tap_count;i++) {
            x = M_PI * ((double)(i - center) - (double)ph / phase_count) * factor;
            if (x == 0) y = 1.0;
            else if (factor == 1.0)
                y = s / x;
            else
                y = sin(x) / x;
            switch(filter_type){
            case SWR_FILTER_TYPE_CUBIC:{
                const float d= -0.5; //first order derivative = -0.5
                x = fabs(((double)(i - center) - (double)ph / phase_count) * factor);
                if(x<1.0) y= 1 - 3*x*x + 2*x*x*x + d*(            -x*x + x*x*x);
                else      y=                       d*(-4 + 8*x - 5*x*x + x*x*x);
                break;}
            case SWR_FILTER_TYPE_BLACKMAN_NUTTALL:
                w = 2.0*x / (factor*tap_count);
                t = -cos(w);
                y *= 0.3635819 - 0.4891775 * t + 0.1365995 * (2*t*t-1) - 0.0106411 * (4*t*t*t - 3*t);
                break;
            case SWR_FILTER_TYPE_KAISER:
                w = 2.0*x / (factor*tap_count*M_PI);
                y *= bessel(kaiser_beta*sqrt(FFMAX(1-w*w, 0)));
                break;
            default:
                av_assert0(0);
            }

            tab[i] = y;
            s = -s;
            if (!ph)
                norm += y;
        }

        /* normalize so that an uniform color remains the same */
        switch(c->format){
        case AV_SAMPLE_FMT_S16P:
            for(i=0;i<tap_count;i++)
                ((int16_t*)filter)[ph * alloc + i] = av_clip_int16(lrintf(tab[i] * scale / norm));
            if (phase_count % 2) break;
            for (i = 0; i < tap_count; i++)
                ((int16_t*)filter)[(phase_count-ph) * alloc + tap_count-1-i] = ((int16_t*)filter)[ph * alloc + i];
            break;
        case AV_SAMPLE_FMT_S32P:
            for(i=0;i<tap_count;i++)
                ((int32_t*)filter)[ph * alloc + i] = av_clipl_int32(llrint(tab[i] * scale / norm));
            if (phase_count % 2) break;
            for (i = 0; i < tap_count; i++)
                ((int32_t*)filter)[(phase_count-ph) * alloc + tap_count-1-i] = ((int32_t*)filter)[ph * alloc + i];
            break;
        case AV_SAMPLE_FMT_FLTP:
            for(i=0;i<tap_count;i++)
                ((float*)filter)[ph * alloc + i] = tab[i] * scale / norm;
            if (phase_count % 2) break;
            for (i = 0; i < tap_count; i++)
                ((float*)filter)[(phase_count-ph) * alloc + tap_count-1-i] = ((float*)filter)[ph * alloc + i];
            break;
        case AV_SAMPLE_FMT_DBLP:
            for(i=0;i<tap_count;i++)
                ((double*)filter)[ph * alloc + i] = tab[i] * scale / norm;
            if (phase_count % 2) break;
            for (i = 0; i < tap_count; i++)
                ((double*)filter)[(phase_count-ph) * alloc + tap_count-1-i] = ((double*)filter)[ph * alloc + i];
            break;
        }
    }
#if 0
    {
#define LEN 1024
        int j,k;
        double sine[LEN + tap_count];
        double filtered[LEN];
        double maxff=-2, minff=2, maxsf=-2, minsf=2;
        for(i=0; i<LEN; i++){
            double ss=0, sf=0, ff=0;
            for(j=0; j<LEN+tap_count; j++)
                sine[j]= cos(i*j*M_PI/LEN);
            for(j=0; j<LEN; j++){
                double sum=0;
                ph=0;
                for(k=0; k<tap_count; k++)
                    sum += filter[ph * tap_count + k] * sine[k+j];
                filtered[j]= sum / (1<<FILTER_SHIFT);
                ss+= sine[j + center] * sine[j + center];
                ff+= filtered[j] * filtered[j];
                sf+= sine[j + center] * filtered[j];
            }
            ss= sqrt(2*ss/LEN);
            ff= sqrt(2*ff/LEN);
            sf= 2*sf/LEN;
            maxff= FFMAX(maxff, ff);
            minff= FFMIN(minff, ff);
            maxsf= FFMAX(maxsf, sf);
            minsf= FFMIN(minsf, sf);
            if(i%11==0){
                av_log(NULL, AV_LOG_ERROR, "i:%4d ss:%f ff:%13.6e-%13.6e sf:%13.6e-%13.6e\n", i, ss, maxff, minff, maxsf, minsf);
                minff=minsf= 2;
                maxff=maxsf= -2;
            }
        }
    }
#endif

    ret = 0;
fail:
    av_free(tab);
    av_free(sin_lut);
    return ret;
}