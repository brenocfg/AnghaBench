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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {int numcomps; TYPE_2__* comps; } ;
typedef  TYPE_3__ opj_image_t ;
struct TYPE_13__ {int height; int width; int* linesize; scalar_t__* data; int /*<<< orphan*/  format; } ;
struct TYPE_12__ {TYPE_1__* comp; } ;
struct TYPE_10__ {int prec; int sgnd; scalar_t__* data; } ;
struct TYPE_9__ {int shift; scalar_t__ depth; } ;
typedef  TYPE_4__ AVPixFmtDescriptor ;
typedef  TYPE_5__ AVFrame ;

/* Variables and functions */
 int FFMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FFMIN (scalar_t__,int) ; 
 TYPE_4__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void libopenjpeg_copy_to_packed16(AVFrame *picture, opj_image_t *image) {
    uint16_t *img_ptr;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(picture->format);
    int index, x, y, c;
    int adjust[4];
    for (x = 0; x < image->numcomps; x++)
        adjust[x] = FFMAX(FFMIN(desc->comp[x].depth - image->comps[x].prec, 8), 0) + desc->comp[x].shift;

    for (y = 0; y < picture->height; y++) {
        index   = y * picture->width;
        img_ptr = (uint16_t *) (picture->data[0] + y * picture->linesize[0]);
        for (x = 0; x < picture->width; x++, index++)
            for (c = 0; c < image->numcomps; c++)
                *img_ptr++ = (1 << image->comps[c].prec - 1) * image->comps[c].sgnd +
                             (unsigned)image->comps[c].data[index] << adjust[c];
    }
}