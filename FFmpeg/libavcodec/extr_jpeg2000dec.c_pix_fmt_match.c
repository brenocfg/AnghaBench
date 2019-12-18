#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_6__ {int nb_components; int log2_chroma_w; int log2_chroma_h; int flags; TYPE_1__* comp; } ;
struct TYPE_5__ {int depth; } ;
typedef  TYPE_2__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_PAL ; 
 int /*<<< orphan*/  av_assert2 (TYPE_2__ const*) ; 
 TYPE_2__* av_pix_fmt_desc_get (int) ; 

__attribute__((used)) static int pix_fmt_match(enum AVPixelFormat pix_fmt, int components,
                         int bpc, uint32_t log2_chroma_wh, int pal8)
{
    int match = 1;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);

    av_assert2(desc);

    if (desc->nb_components != components) {
        return 0;
    }

    switch (components) {
    case 4:
        match = match && desc->comp[3].depth >= bpc &&
                         (log2_chroma_wh >> 14 & 3) == 0 &&
                         (log2_chroma_wh >> 12 & 3) == 0;
    case 3:
        match = match && desc->comp[2].depth >= bpc &&
                         (log2_chroma_wh >> 10 & 3) == desc->log2_chroma_w &&
                         (log2_chroma_wh >>  8 & 3) == desc->log2_chroma_h;
    case 2:
        match = match && desc->comp[1].depth >= bpc &&
                         (log2_chroma_wh >>  6 & 3) == desc->log2_chroma_w &&
                         (log2_chroma_wh >>  4 & 3) == desc->log2_chroma_h;

    case 1:
        match = match && desc->comp[0].depth >= bpc &&
                         (log2_chroma_wh >>  2 & 3) == 0 &&
                         (log2_chroma_wh       & 3) == 0 &&
                         (desc->flags & AV_PIX_FMT_FLAG_PAL) == pal8 * AV_PIX_FMT_FLAG_PAL;
    }
    return match;
}