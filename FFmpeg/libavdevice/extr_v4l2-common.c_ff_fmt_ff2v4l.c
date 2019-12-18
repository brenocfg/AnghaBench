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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_2__ {scalar_t__ codec_id; int ff_fmt; int /*<<< orphan*/  v4l2_fmt; } ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_NONE ; 
 int AV_PIX_FMT_NONE ; 
 TYPE_1__* ff_fmt_conversion_table ; 

uint32_t ff_fmt_ff2v4l(enum AVPixelFormat pix_fmt, enum AVCodecID codec_id)
{
    int i;

    for (i = 0; ff_fmt_conversion_table[i].codec_id != AV_CODEC_ID_NONE; i++) {
        if ((codec_id == AV_CODEC_ID_NONE ||
             ff_fmt_conversion_table[i].codec_id == codec_id) &&
            (pix_fmt == AV_PIX_FMT_NONE ||
             ff_fmt_conversion_table[i].ff_fmt == pix_fmt)) {
            return ff_fmt_conversion_table[i].v4l2_fmt;
        }
    }

    return 0;
}