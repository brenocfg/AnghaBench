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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PIX_FMT_FLAG_PAL ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFALIGN (int,int) ; 
 int FF_PSEUDOPAL ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int av_image_check_size (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int av_image_fill_linesizes (int*,int,int) ; 
 int av_image_fill_pointers (int /*<<< orphan*/ **,int,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 TYPE_1__* av_pix_fmt_desc_get (int) ; 
 int /*<<< orphan*/  avpriv_set_systematic_pal2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int av_image_alloc(uint8_t *pointers[4], int linesizes[4],
                   int w, int h, enum AVPixelFormat pix_fmt, int align)
{
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(pix_fmt);
    int i, ret;
    uint8_t *buf;

    if (!desc)
        return AVERROR(EINVAL);

    if ((ret = av_image_check_size(w, h, 0, NULL)) < 0)
        return ret;
    if ((ret = av_image_fill_linesizes(linesizes, pix_fmt, align>7 ? FFALIGN(w, 8) : w)) < 0)
        return ret;

    for (i = 0; i < 4; i++)
        linesizes[i] = FFALIGN(linesizes[i], align);

    if ((ret = av_image_fill_pointers(pointers, pix_fmt, h, NULL, linesizes)) < 0)
        return ret;
    buf = av_malloc(ret + align);
    if (!buf)
        return AVERROR(ENOMEM);
    if ((ret = av_image_fill_pointers(pointers, pix_fmt, h, buf, linesizes)) < 0) {
        av_free(buf);
        return ret;
    }
    if (desc->flags & AV_PIX_FMT_FLAG_PAL || (desc->flags & FF_PSEUDOPAL && pointers[1])) {
        avpriv_set_systematic_pal2((uint32_t*)pointers[1], pix_fmt);
        if (align < 4) {
            av_log(NULL, AV_LOG_ERROR, "Formats with a palette require a minimum alignment of 4\n");
            return AVERROR(EINVAL);
        }
    }

    if ((desc->flags & AV_PIX_FMT_FLAG_PAL ||
         desc->flags & FF_PSEUDOPAL) && pointers[1] &&
        pointers[1] - pointers[0] > linesizes[0] * h) {
        /* zero-initialize the padding before the palette */
        memset(pointers[0] + linesizes[0] * h, 0,
               pointers[1] - pointers[0] - linesizes[0] * h);
    }

    return ret;
}