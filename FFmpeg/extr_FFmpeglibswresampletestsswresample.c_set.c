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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;

/* Variables and functions */
#define  AV_SAMPLE_FMT_DBL 132 
#define  AV_SAMPLE_FMT_FLT 131 
#define  AV_SAMPLE_FMT_S16 130 
#define  AV_SAMPLE_FMT_S32 129 
#define  AV_SAMPLE_FMT_U8 128 
 int /*<<< orphan*/  av_assert2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_clip_int16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_clip_uint8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_clipl_int32 (int /*<<< orphan*/ ) ; 
 int av_get_alt_sample_fmt (int,int /*<<< orphan*/ ) ; 
 scalar_t__ av_sample_fmt_is_planar (int) ; 
 int /*<<< orphan*/  llrint (double) ; 
 int /*<<< orphan*/  lrint (double) ; 

__attribute__((used)) static void  set(uint8_t *a[], int ch, int index, int ch_count, enum AVSampleFormat f, double v){
    uint8_t *p;
    if(av_sample_fmt_is_planar(f)){
        f= av_get_alt_sample_fmt(f, 0);
        p= a[ch];
    }else{
        p= a[0];
        index= ch + index*ch_count;
    }
    switch(f){
    case AV_SAMPLE_FMT_U8 : ((uint8_t*)p)[index]= av_clip_uint8 (lrint((v+1.0)*127));     break;
    case AV_SAMPLE_FMT_S16: ((int16_t*)p)[index]= av_clip_int16 (lrint(v*32767));         break;
    case AV_SAMPLE_FMT_S32: ((int32_t*)p)[index]= av_clipl_int32(llrint(v*2147483647));   break;
    case AV_SAMPLE_FMT_FLT: ((float  *)p)[index]= v;                                      break;
    case AV_SAMPLE_FMT_DBL: ((double *)p)[index]= v;                                      break;
    default: av_assert2(0);
    }
}