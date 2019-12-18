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
struct TYPE_3__ {int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ VP8Context ;

/* Variables and functions */
 int AV_PIX_FMT_CUDA ; 
 int AV_PIX_FMT_NONE ; 
 int AV_PIX_FMT_VAAPI ; 
 int AV_PIX_FMT_YUV420P ; 
 int ff_get_format (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static enum AVPixelFormat get_pixel_format(VP8Context *s)
{
    enum AVPixelFormat pix_fmts[] = {
#if CONFIG_VP8_VAAPI_HWACCEL
        AV_PIX_FMT_VAAPI,
#endif
#if CONFIG_VP8_NVDEC_HWACCEL
        AV_PIX_FMT_CUDA,
#endif
        AV_PIX_FMT_YUV420P,
        AV_PIX_FMT_NONE,
    };

    return ff_get_format(s->avctx, pix_fmts);
}