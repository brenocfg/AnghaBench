#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {unsigned long width; unsigned long height; unsigned long datalen; int* data; } ;
typedef  TYPE_4__ zbar_image_t ;
struct TYPE_13__ {unsigned long bpp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_12__ {int packorder; int xsub2; } ;
struct TYPE_14__ {TYPE_2__ rgb; TYPE_1__ yuv; } ;
struct TYPE_16__ {TYPE_3__ p; } ;
typedef  TYPE_5__ zbar_format_def_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int RGB_OFFSET (int /*<<< orphan*/ ) ; 
 int RGB_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  convert_write_rgb (int*,int,unsigned long) ; 
 int* malloc (unsigned long) ; 
 int uvp_size (TYPE_4__ const*,TYPE_5__ const*) ; 

__attribute__((used)) static void convert_yuv_to_rgb (zbar_image_t *dst,
                                const zbar_format_def_t *dstfmt,
                                const zbar_image_t *src,
                                const zbar_format_def_t *srcfmt)
{
    uint8_t *dstp;
    unsigned long dstn = dst->width * dst->height;
    int drbits, drbit0, dgbits, dgbit0, dbbits, dbbit0;
    const uint8_t *srcp;
    unsigned srcl, x, y;
    uint32_t p = 0;

    dst->datalen = dstn * dstfmt->p.rgb.bpp;
    dst->data = malloc(dst->datalen);
    if(!dst->data) return;
    dstp = (void*)dst->data;

    drbits = RGB_SIZE(dstfmt->p.rgb.red);
    drbit0 = RGB_OFFSET(dstfmt->p.rgb.red);
    dgbits = RGB_SIZE(dstfmt->p.rgb.green);
    dgbit0 = RGB_OFFSET(dstfmt->p.rgb.green);
    dbbits = RGB_SIZE(dstfmt->p.rgb.blue);
    dbbit0 = RGB_OFFSET(dstfmt->p.rgb.blue);

    assert(src->datalen >= (src->width * src->height +
                            uvp_size(src, srcfmt) * 2));
    srcp = src->data;
    if(srcfmt->p.yuv.packorder & 2)
        srcp++;

    assert(srcfmt->p.yuv.xsub2 == 1);
    srcl = src->width + (src->width >> 1);
    for(y = 0; y < dst->height; y++) {
        if(y >= src->height)
            srcp -= srcl;
        for(x = 0; x < dst->width; x++) {
            if(x < src->width) {
                uint8_t y0 = *(srcp++);
                srcp++;

                if(y0 <= 16)
                    y0 = 0;
                else if(y0 >= 235)
                    y0 = 255;
                else
                    y0 = (uint16_t)(y0 - 16) * 255 / 219;

                p = (((y0 >> drbits) << drbit0) |
                     ((y0 >> dgbits) << dgbit0) |
                     ((y0 >> dbbits) << dbbit0));
            }
            convert_write_rgb(dstp, p, dstfmt->p.rgb.bpp);
            dstp += dstfmt->p.rgb.bpp;
        }
        if(x < src->width)
            srcp += (src->width - x) * 2;
    }
}