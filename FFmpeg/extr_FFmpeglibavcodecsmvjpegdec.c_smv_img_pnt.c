#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_5__ {int flags; int nb_components; int /*<<< orphan*/  log2_chroma_h; TYPE_1__* comp; } ;
struct TYPE_4__ {scalar_t__ plane; } ;
typedef  TYPE_2__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int AV_PIX_FMT_FLAG_HWACCEL ; 
 int AV_PIX_FMT_FLAG_PAL ; 
 int FFMAX (int,scalar_t__) ; 
 int FF_PSEUDOPAL ; 
 TYPE_2__* av_pix_fmt_desc_get (int) ; 
 int /*<<< orphan*/  smv_img_pnt_plane (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int const,int,int) ; 

__attribute__((used)) static inline void smv_img_pnt(uint8_t *dst_data[4], uint8_t *src_data[4],
                               const int src_linesizes[4],
                               enum AVPixelFormat pix_fmt, int width, int height,
                               int nlines)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    int i, planes_nb = 0;

    if (desc->flags & AV_PIX_FMT_FLAG_HWACCEL)
        return;

    for (i = 0; i < desc->nb_components; i++)
        planes_nb = FFMAX(planes_nb, desc->comp[i].plane + 1);

    for (i = 0; i < planes_nb; i++) {
        int h = height;
        if (i == 1 || i == 2) {
            h = AV_CEIL_RSHIFT(height, desc->log2_chroma_h);
        }
        smv_img_pnt_plane(&dst_data[i], src_data[i],
            src_linesizes[i], h, nlines);
    }
    if (desc->flags & AV_PIX_FMT_FLAG_PAL ||
        desc->flags & FF_PSEUDOPAL)
        dst_data[1] = src_data[1];
}