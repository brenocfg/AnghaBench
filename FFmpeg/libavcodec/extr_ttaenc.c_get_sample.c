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
typedef  int int32_t ;
typedef  int int16_t ;
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_3__ {int** data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int AV_SAMPLE_FMT_S16 ; 
 int AV_SAMPLE_FMT_U8 ; 

__attribute__((used)) static int32_t get_sample(const AVFrame *frame, int sample,
                          enum AVSampleFormat format)
{
    int32_t ret;

    if (format == AV_SAMPLE_FMT_U8) {
        ret = frame->data[0][sample] - 0x80;
    } else if (format == AV_SAMPLE_FMT_S16) {
        const int16_t *ptr = (const int16_t *)frame->data[0];
        ret = ptr[sample];
    } else {
        const int32_t *ptr = (const int32_t *)frame->data[0];
        ret = ptr[sample] >> 8;
    }

    return ret;
}