#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int numcomps; TYPE_2__* comps; } ;
typedef  TYPE_3__ opj_image_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_10__ {int nb_components; int log2_chroma_w; int log2_chroma_h; TYPE_1__* comp; } ;
struct TYPE_8__ {int dx; int dy; int /*<<< orphan*/  prec; } ;
struct TYPE_7__ {int /*<<< orphan*/  depth; } ;
typedef  TYPE_4__ AVPixFmtDescriptor ;

/* Variables and functions */
 TYPE_4__* av_pix_fmt_desc_get (int) ; 

__attribute__((used)) static inline int libopenjpeg_matches_pix_fmt(const opj_image_t *image, enum AVPixelFormat pix_fmt)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    int match = 1;

    if (desc->nb_components != image->numcomps) {
        return 0;
    }

    switch (desc->nb_components) {
    case 4:
        match = match &&
                desc->comp[3].depth >= image->comps[3].prec &&
                1 == image->comps[3].dx &&
                1 == image->comps[3].dy;
    case 3:
        match = match &&
                desc->comp[2].depth >= image->comps[2].prec &&
                1 << desc->log2_chroma_w == image->comps[2].dx &&
                1 << desc->log2_chroma_h == image->comps[2].dy;
    case 2:
        match = match &&
                desc->comp[1].depth >= image->comps[1].prec &&
                1 << desc->log2_chroma_w == image->comps[1].dx &&
                1 << desc->log2_chroma_h == image->comps[1].dy;
    case 1:
        match = match &&
                desc->comp[0].depth >= image->comps[0].prec &&
                1 == image->comps[0].dx &&
                1 == image->comps[0].dy;
    default:
        break;
    }

    return match;
}