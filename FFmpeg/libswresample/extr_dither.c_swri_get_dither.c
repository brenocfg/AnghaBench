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
typedef  double int32_t ;
typedef  double int16_t ;
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_4__ {double noise_scale; int method; } ;
struct TYPE_5__ {TYPE_1__ dither; } ;
typedef  TYPE_2__ SwrContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_SAMPLE_FMT_DBLP 133 
#define  AV_SAMPLE_FMT_FLTP 132 
#define  AV_SAMPLE_FMT_S16P 131 
#define  AV_SAMPLE_FMT_S32P 130 
 int /*<<< orphan*/  ENOMEM ; 
 int SWR_DITHER_NB ; 
#define  SWR_DITHER_RECTANGULAR 129 
#define  SWR_DITHER_TRIANGULAR_HIGHPASS 128 
 int TMP_EXTRA ; 
 double UINT_MAX ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_free (double*) ; 
 double* av_malloc_array (int,int) ; 
 double sqrt (int) ; 

int swri_get_dither(SwrContext *s, void *dst, int len, unsigned seed, enum AVSampleFormat noise_fmt) {
    double scale = s->dither.noise_scale;
#define TMP_EXTRA 2
    double *tmp = av_malloc_array(len + TMP_EXTRA, sizeof(double));
    int i;

    if (!tmp)
        return AVERROR(ENOMEM);

    for(i=0; i<len + TMP_EXTRA; i++){
        double v;
        seed = seed* 1664525 + 1013904223;

        switch(s->dither.method){
            case SWR_DITHER_RECTANGULAR: v= ((double)seed) / UINT_MAX - 0.5; break;
            default:
                av_assert0(s->dither.method < SWR_DITHER_NB);
                v = ((double)seed) / UINT_MAX;
                seed = seed*1664525 + 1013904223;
                v-= ((double)seed) / UINT_MAX;
                break;
        }
        tmp[i] = v;
    }

    for(i=0; i<len; i++){
        double v;

        switch(s->dither.method){
            default:
                av_assert0(s->dither.method < SWR_DITHER_NB);
                v = tmp[i];
                break;
            case SWR_DITHER_TRIANGULAR_HIGHPASS :
                v = (- tmp[i] + 2*tmp[i+1] - tmp[i+2]) / sqrt(6);
                break;
        }

        v*= scale;

        switch(noise_fmt){
            case AV_SAMPLE_FMT_S16P: ((int16_t*)dst)[i] = v; break;
            case AV_SAMPLE_FMT_S32P: ((int32_t*)dst)[i] = v; break;
            case AV_SAMPLE_FMT_FLTP: ((float  *)dst)[i] = v; break;
            case AV_SAMPLE_FMT_DBLP: ((double *)dst)[i] = v; break;
            default: av_assert0(0);
        }
    }

    av_free(tmp);
    return 0;
}