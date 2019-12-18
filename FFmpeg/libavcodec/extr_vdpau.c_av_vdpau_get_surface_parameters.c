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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  VdpChromaType ;
struct TYPE_3__ {int coded_width; int coded_height; int sw_pix_fmt; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_PIX_FMT_YUV420P 133 
#define  AV_PIX_FMT_YUV422P 132 
#define  AV_PIX_FMT_YUV444P 131 
#define  AV_PIX_FMT_YUVJ420P 130 
#define  AV_PIX_FMT_YUVJ422P 129 
#define  AV_PIX_FMT_YUVJ444P 128 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  VDP_CHROMA_TYPE_420 ; 
 int /*<<< orphan*/  VDP_CHROMA_TYPE_422 ; 
 int /*<<< orphan*/  VDP_CHROMA_TYPE_444 ; 

int av_vdpau_get_surface_parameters(AVCodecContext *avctx,
                                    VdpChromaType *type,
                                    uint32_t *width, uint32_t *height)
{
    VdpChromaType t;
    uint32_t w = avctx->coded_width;
    uint32_t h = avctx->coded_height;

    /* See <vdpau/vdpau.h> for per-type alignment constraints. */
    switch (avctx->sw_pix_fmt) {
    case AV_PIX_FMT_YUV420P:
    case AV_PIX_FMT_YUVJ420P:
        t = VDP_CHROMA_TYPE_420;
        w = (w + 1) & ~1;
        h = (h + 3) & ~3;
        break;
    case AV_PIX_FMT_YUV422P:
    case AV_PIX_FMT_YUVJ422P:
        t = VDP_CHROMA_TYPE_422;
        w = (w + 1) & ~1;
        h = (h + 1) & ~1;
        break;
    case AV_PIX_FMT_YUV444P:
    case AV_PIX_FMT_YUVJ444P:
        t = VDP_CHROMA_TYPE_444;
        h = (h + 1) & ~1;
        break;
    default:
        return AVERROR(ENOSYS);
    }

    if (type)
        *type = t;
    if (width)
        *width = w;
    if (height)
        *height = h;
    return 0;
}