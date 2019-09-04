#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_10__ {int BitDepthLuma; int BitDepthChroma; int Shift; int FrameRateExtN; int FrameRateExtD; int /*<<< orphan*/  PicStruct; int /*<<< orphan*/  CropH; void* Height; int /*<<< orphan*/  CropW; void* Width; scalar_t__ FourCC; int /*<<< orphan*/  ChromaFormat; } ;
struct TYPE_11__ {TYPE_2__ Info; } ;
typedef  TYPE_3__ mfxFrameSurface1 ;
struct TYPE_13__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  sw_format; } ;
struct TYPE_12__ {scalar_t__ log2_chroma_w; scalar_t__ log2_chroma_h; TYPE_1__* comp; } ;
struct TYPE_9__ {int depth; } ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVHWFramesContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 void* FFALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MFX_CHROMAFORMAT_YUV420 ; 
 int /*<<< orphan*/  MFX_CHROMAFORMAT_YUV422 ; 
 int /*<<< orphan*/  MFX_CHROMAFORMAT_YUV444 ; 
 int /*<<< orphan*/  MFX_PICSTRUCT_PROGRESSIVE ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 scalar_t__ qsv_fourcc_from_pix_fmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qsv_init_surface(AVHWFramesContext *ctx, mfxFrameSurface1 *surf)
{
    const AVPixFmtDescriptor *desc;
    uint32_t fourcc;

    desc = av_pix_fmt_desc_get(ctx->sw_format);
    if (!desc)
        return AVERROR(EINVAL);

    fourcc = qsv_fourcc_from_pix_fmt(ctx->sw_format);
    if (!fourcc)
        return AVERROR(EINVAL);

    surf->Info.BitDepthLuma   = desc->comp[0].depth;
    surf->Info.BitDepthChroma = desc->comp[0].depth;
    surf->Info.Shift          = desc->comp[0].depth > 8;

    if (desc->log2_chroma_w && desc->log2_chroma_h)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV420;
    else if (desc->log2_chroma_w)
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV422;
    else
        surf->Info.ChromaFormat   = MFX_CHROMAFORMAT_YUV444;

    surf->Info.FourCC         = fourcc;
    surf->Info.Width          = FFALIGN(ctx->width, 16);
    surf->Info.CropW          = ctx->width;
    surf->Info.Height         = FFALIGN(ctx->height, 16);
    surf->Info.CropH          = ctx->height;
    surf->Info.FrameRateExtN  = 25;
    surf->Info.FrameRateExtD  = 1;
    surf->Info.PicStruct      = MFX_PICSTRUCT_PROGRESSIVE;

    return 0;
}