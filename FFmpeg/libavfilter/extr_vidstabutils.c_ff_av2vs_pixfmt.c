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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  int /*<<< orphan*/  VSPixelFormat ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  AV_PIX_FMT_BGR24 138 
#define  AV_PIX_FMT_GRAY8 137 
#define  AV_PIX_FMT_RGB24 136 
#define  AV_PIX_FMT_RGBA 135 
#define  AV_PIX_FMT_YUV410P 134 
#define  AV_PIX_FMT_YUV411P 133 
#define  AV_PIX_FMT_YUV420P 132 
#define  AV_PIX_FMT_YUV422P 131 
#define  AV_PIX_FMT_YUV440P 130 
#define  AV_PIX_FMT_YUV444P 129 
#define  AV_PIX_FMT_YUVA420P 128 
 int /*<<< orphan*/  PF_BGR24 ; 
 int /*<<< orphan*/  PF_GRAY8 ; 
 int /*<<< orphan*/  PF_NONE ; 
 int /*<<< orphan*/  PF_RGB24 ; 
 int /*<<< orphan*/  PF_RGBA ; 
 int /*<<< orphan*/  PF_YUV410P ; 
 int /*<<< orphan*/  PF_YUV411P ; 
 int /*<<< orphan*/  PF_YUV420P ; 
 int /*<<< orphan*/  PF_YUV422P ; 
 int /*<<< orphan*/  PF_YUV440P ; 
 int /*<<< orphan*/  PF_YUV444P ; 
 int /*<<< orphan*/  PF_YUVA420P ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

VSPixelFormat ff_av2vs_pixfmt(AVFilterContext *ctx, enum AVPixelFormat pf)
{
    switch (pf) {
    case AV_PIX_FMT_YUV420P:  return PF_YUV420P;
    case AV_PIX_FMT_YUV422P:  return PF_YUV422P;
    case AV_PIX_FMT_YUV444P:  return PF_YUV444P;
    case AV_PIX_FMT_YUV410P:  return PF_YUV410P;
    case AV_PIX_FMT_YUV411P:  return PF_YUV411P;
    case AV_PIX_FMT_YUV440P:  return PF_YUV440P;
    case AV_PIX_FMT_YUVA420P: return PF_YUVA420P;
    case AV_PIX_FMT_GRAY8:    return PF_GRAY8;
    case AV_PIX_FMT_RGB24:    return PF_RGB24;
    case AV_PIX_FMT_BGR24:    return PF_BGR24;
    case AV_PIX_FMT_RGBA:     return PF_RGBA;
    default:
        av_log(ctx, AV_LOG_ERROR, "cannot deal with pixel format %i\n", pf);
        return PF_NONE;
    }
}