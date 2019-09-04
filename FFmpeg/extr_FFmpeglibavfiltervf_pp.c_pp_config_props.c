#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_1__* dst; } ;
struct TYPE_6__ {int /*<<< orphan*/  pp_ctx; } ;
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ PPFilterContext ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_GBRP 138 
#define  AV_PIX_FMT_GRAY8 137 
#define  AV_PIX_FMT_YUV411P 136 
#define  AV_PIX_FMT_YUV420P 135 
#define  AV_PIX_FMT_YUV422P 134 
#define  AV_PIX_FMT_YUV440P 133 
#define  AV_PIX_FMT_YUV444P 132 
#define  AV_PIX_FMT_YUVJ420P 131 
#define  AV_PIX_FMT_YUVJ422P 130 
#define  AV_PIX_FMT_YUVJ440P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  ENOMEM ; 
 int PP_CPU_CAPS_AUTO ; 
 int PP_FORMAT_411 ; 
 int PP_FORMAT_420 ; 
 int PP_FORMAT_422 ; 
 int PP_FORMAT_440 ; 
 int PP_FORMAT_444 ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_get_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pp_config_props(AVFilterLink *inlink)
{
    int flags = PP_CPU_CAPS_AUTO;
    PPFilterContext *pp = inlink->dst->priv;

    switch (inlink->format) {
    case AV_PIX_FMT_GRAY8:
    case AV_PIX_FMT_YUVJ420P:
    case AV_PIX_FMT_YUV420P: flags |= PP_FORMAT_420; break;
    case AV_PIX_FMT_YUVJ422P:
    case AV_PIX_FMT_YUV422P: flags |= PP_FORMAT_422; break;
    case AV_PIX_FMT_YUV411P: flags |= PP_FORMAT_411; break;
    case AV_PIX_FMT_GBRP:
    case AV_PIX_FMT_YUVJ444P:
    case AV_PIX_FMT_YUV444P: flags |= PP_FORMAT_444; break;
    case AV_PIX_FMT_YUVJ440P:
    case AV_PIX_FMT_YUV440P: flags |= PP_FORMAT_440; break;
    default: av_assert0(0);
    }

    pp->pp_ctx = pp_get_context(inlink->w, inlink->h, flags);
    if (!pp->pp_ctx)
        return AVERROR(ENOMEM);
    return 0;
}