#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int datalen; int width; int height; scalar_t__ data; } ;
typedef  TYPE_3__ zbar_image_t ;
struct TYPE_11__ {int bpp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_12__ {TYPE_1__ rgb; } ;
struct TYPE_14__ {TYPE_2__ p; } ;
typedef  TYPE_4__ zbar_format_def_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  unsigned int uint32_t ;

/* Variables and functions */
 int RGB_OFFSET (int /*<<< orphan*/ ) ; 
 int RGB_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  convert_write_rgb (int /*<<< orphan*/ *,unsigned int,int) ; 
 scalar_t__ malloc (int) ; 
 unsigned long uvp_size (TYPE_3__ const*,TYPE_4__ const*) ; 

__attribute__((used)) static void convert_yuvp_to_rgb (zbar_image_t *dst,
                                 const zbar_format_def_t *dstfmt,
                                 const zbar_image_t *src,
                                 const zbar_format_def_t *srcfmt)
{
    uint8_t *dstp, *srcy;
    int drbits, drbit0, dgbits, dgbit0, dbbits, dbbit0;
    unsigned long srcm, srcn;
    unsigned x, y;
    uint32_t p = 0;

    dst->datalen = dst->width * dst->height * dstfmt->p.rgb.bpp;
    dst->data = malloc(dst->datalen);
    if(!dst->data) return;
    dstp = (void*)dst->data;

    drbits = RGB_SIZE(dstfmt->p.rgb.red);
    drbit0 = RGB_OFFSET(dstfmt->p.rgb.red);
    dgbits = RGB_SIZE(dstfmt->p.rgb.green);
    dgbit0 = RGB_OFFSET(dstfmt->p.rgb.green);
    dbbits = RGB_SIZE(dstfmt->p.rgb.blue);
    dbbit0 = RGB_OFFSET(dstfmt->p.rgb.blue);

    srcm = uvp_size(src, srcfmt);
    srcn = src->width * src->height;
    assert(src->datalen >= srcn + 2 * srcm);
    srcy = (void*)src->data;

    for(y = 0; y < dst->height; y++) {
        if(y >= src->height)
            srcy -= src->width;
        for(x = 0; x < dst->width; x++) {
            if(x < src->width) {
                /* FIXME color space? */
                unsigned y0 = *(srcy++);
                p = (((y0 >> drbits) << drbit0) |
                     ((y0 >> dgbits) << dgbit0) |
                     ((y0 >> dbbits) << dbbit0));
            }
            convert_write_rgb(dstp, p, dstfmt->p.rgb.bpp);
            dstp += dstfmt->p.rgb.bpp;
        }
        if(x < src->width)
            srcy += (src->width - x);
    }
}