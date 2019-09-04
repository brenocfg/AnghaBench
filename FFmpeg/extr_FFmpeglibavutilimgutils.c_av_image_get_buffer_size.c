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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int FFALIGN (int,int) ; 
 int FF_PSEUDOPAL ; 
 int av_image_check_size (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int av_image_fill_arrays (int /*<<< orphan*/ **,int*,int /*<<< orphan*/ *,int,int,int,int) ; 
 TYPE_1__* av_pix_fmt_desc_get (int) ; 

int av_image_get_buffer_size(enum AVPixelFormat pix_fmt,
                             int width, int height, int align)
{
    uint8_t *data[4];
    int linesize[4];
    int ret;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    if (!desc)
        return AVERROR(EINVAL);

    ret = av_image_check_size(width, height, 0, NULL);
    if (ret < 0)
        return ret;

    // do not include palette for these pseudo-paletted formats
    if (desc->flags & FF_PSEUDOPAL)
        return FFALIGN(width, align) * height;

    return av_image_fill_arrays(data, linesize, NULL, pix_fmt,
                                width, height, align);
}