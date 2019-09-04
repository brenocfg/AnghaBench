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
typedef  double uint8_t ;
typedef  double int32_t ;
typedef  double int16_t ;
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;

/* Variables and functions */
#define  AV_SAMPLE_FMT_DBL 132 
#define  AV_SAMPLE_FMT_FLT 131 
#define  AV_SAMPLE_FMT_S16 130 
#define  AV_SAMPLE_FMT_S32 129 
#define  AV_SAMPLE_FMT_U8 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int av_get_alt_sample_fmt (int,int /*<<< orphan*/ ) ; 
 scalar_t__ av_sample_fmt_is_planar (int) ; 

__attribute__((used)) static double get(uint8_t *a[], int ch, int index, int ch_count, enum AVSampleFormat f){
    const uint8_t *p;
    if(av_sample_fmt_is_planar(f)){
        f= av_get_alt_sample_fmt(f, 0);
        p= a[ch];
    }else{
        p= a[0];
        index= ch + index*ch_count;
    }

    switch(f){
    case AV_SAMPLE_FMT_U8 : return ((const uint8_t*)p)[index]/127.0-1.0;
    case AV_SAMPLE_FMT_S16: return ((const int16_t*)p)[index]/32767.0;
    case AV_SAMPLE_FMT_S32: return ((const int32_t*)p)[index]/2147483647.0;
    case AV_SAMPLE_FMT_FLT: return ((const float  *)p)[index];
    case AV_SAMPLE_FMT_DBL: return ((const double *)p)[index];
    default: av_assert0(0);
    }
}