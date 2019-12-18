#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_2__ {scalar_t__ codec_id; scalar_t__ v4l2_fmt; int ff_fmt; } ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_NONE ; 
 int AV_PIX_FMT_NONE ; 
 TYPE_1__* ff_fmt_conversion_table ; 

enum AVPixelFormat ff_fmt_v4l2ff(uint32_t v4l2_fmt, enum AVCodecID codec_id)
{
    int i;

    for (i = 0; ff_fmt_conversion_table[i].codec_id != AV_CODEC_ID_NONE; i++) {
        if (ff_fmt_conversion_table[i].v4l2_fmt == v4l2_fmt &&
            ff_fmt_conversion_table[i].codec_id == codec_id) {
            return ff_fmt_conversion_table[i].ff_fmt;
        }
    }

    return AV_PIX_FMT_NONE;
}