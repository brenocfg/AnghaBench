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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct aom_image {int d_w; int d_h; int x_chroma_shift; int y_chroma_shift; int* stride; scalar_t__* planes; } ;
struct TYPE_6__ {int* linesize; int /*<<< orphan*/ ** data; int /*<<< orphan*/  format; } ;
struct TYPE_5__ {int nb_components; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 TYPE_1__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void image_copy_16_to_8(AVFrame *pic, struct aom_image *img)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pic->format);
    int i;

    for (i = 0; i < desc->nb_components; i++) {
        int w = img->d_w;
        int h = img->d_h;
        int x, y;

        if (i) {
            w = (w + img->x_chroma_shift) >> img->x_chroma_shift;
            h = (h + img->y_chroma_shift) >> img->y_chroma_shift;
        }

        for (y = 0; y < h; y++) {
            uint16_t *src = (uint16_t *)(img->planes[i] + y * img->stride[i]);
            uint8_t *dst = pic->data[i] + y * pic->linesize[i];
            for (x = 0; x < w; x++)
                *dst++ = *src++;
        }
    }
}