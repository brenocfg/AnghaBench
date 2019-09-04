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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {scalar_t__ type; int width; int height; int format; int align; } ;
typedef  TYPE_1__ FFFramePool ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_assert0 (int) ; 

int ff_frame_pool_get_video_config(FFFramePool *pool,
                                   int *width,
                                   int *height,
                                   enum AVPixelFormat *format,
                                   int *align)
{
    if (!pool)
        return AVERROR(EINVAL);

    av_assert0(pool->type == AVMEDIA_TYPE_VIDEO);

    *width = pool->width;
    *height = pool->height;
    *format = pool->format;
    *align = pool->align;

    return 0;
}