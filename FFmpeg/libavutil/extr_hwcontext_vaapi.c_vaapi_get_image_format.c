#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  int /*<<< orphan*/  VAImageFormat ;
struct TYPE_8__ {int nb_formats; TYPE_2__* formats; } ;
typedef  TYPE_3__ VAAPIDeviceContext ;
struct TYPE_9__ {TYPE_1__* internal; } ;
struct TYPE_7__ {int pix_fmt; int /*<<< orphan*/  image_format; } ;
struct TYPE_6__ {TYPE_3__* priv; } ;
typedef  TYPE_4__ AVHWDeviceContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 

__attribute__((used)) static int vaapi_get_image_format(AVHWDeviceContext *hwdev,
                                  enum AVPixelFormat pix_fmt,
                                  VAImageFormat **image_format)
{
    VAAPIDeviceContext *ctx = hwdev->internal->priv;
    int i;

    for (i = 0; i < ctx->nb_formats; i++) {
        if (ctx->formats[i].pix_fmt == pix_fmt) {
            if (image_format)
                *image_format = &ctx->formats[i].image_format;
            return 0;
        }
    }
    return AVERROR(EINVAL);
}