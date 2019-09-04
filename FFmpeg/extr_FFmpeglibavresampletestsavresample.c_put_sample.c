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
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;

/* Variables and functions */
#define  AV_SAMPLE_FMT_DBL 132 
#define  AV_SAMPLE_FMT_FLT 131 
#define  AV_SAMPLE_FMT_S16 130 
#define  AV_SAMPLE_FMT_S32 129 
#define  AV_SAMPLE_FMT_U8 128 
 int av_get_packed_sample_fmt (int) ; 
 int /*<<< orphan*/  put_sample_dbl (void**,int,int,int,int,double) ; 
 int /*<<< orphan*/  put_sample_flt (void**,int,int,int,int,double) ; 
 int /*<<< orphan*/  put_sample_s16 (void**,int,int,int,int,double) ; 
 int /*<<< orphan*/  put_sample_s32 (void**,int,int,int,int,double) ; 
 int /*<<< orphan*/  put_sample_u8 (void**,int,int,int,int,double) ; 

__attribute__((used)) static void put_sample(void **data, enum AVSampleFormat sample_fmt,
                       int channels, int sample, int ch, double v_dbl)
{
    switch (av_get_packed_sample_fmt(sample_fmt)) {
    case AV_SAMPLE_FMT_U8:
        put_sample_u8(data, sample_fmt, channels, sample, ch, v_dbl);
        break;
    case AV_SAMPLE_FMT_S16:
        put_sample_s16(data, sample_fmt, channels, sample, ch, v_dbl);
        break;
    case AV_SAMPLE_FMT_S32:
        put_sample_s32(data, sample_fmt, channels, sample, ch, v_dbl);
        break;
    case AV_SAMPLE_FMT_FLT:
        put_sample_flt(data, sample_fmt, channels, sample, ch, v_dbl);
        break;
    case AV_SAMPLE_FMT_DBL:
        put_sample_dbl(data, sample_fmt, channels, sample, ch, v_dbl);
        break;
    }
}