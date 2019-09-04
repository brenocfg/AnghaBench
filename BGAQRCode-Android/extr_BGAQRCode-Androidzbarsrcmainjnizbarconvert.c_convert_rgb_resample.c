#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned long width; unsigned long height; unsigned long datalen; int* data; } ;
typedef  TYPE_3__ zbar_image_t ;
struct TYPE_9__ {unsigned long bpp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_10__ {TYPE_1__ rgb; } ;
struct TYPE_12__ {TYPE_2__ p; } ;
typedef  TYPE_4__ zbar_format_def_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int RGB_OFFSET (int /*<<< orphan*/ ) ; 
 int RGB_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int convert_read_rgb (int const*,unsigned int) ; 
 int /*<<< orphan*/  convert_write_rgb (int*,int,unsigned int) ; 
 int* malloc (unsigned long) ; 

__attribute__((used)) static void convert_rgb_resample (zbar_image_t *dst,
                                  const zbar_format_def_t *dstfmt,
                                  const zbar_image_t *src,
                                  const zbar_format_def_t *srcfmt)
{
    unsigned long dstn = dst->width * dst->height;
    uint8_t *dstp;
    int drbits, drbit0, dgbits, dgbit0, dbbits, dbbit0;
    int srbits, srbit0, sgbits, sgbit0, sbbits, sbbit0;
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

    assert(src->datalen >= (src->width * src->height * srcfmt->p.rgb.bpp));
    srcp = src->data;

    srbits = RGB_SIZE(srcfmt->p.rgb.red);
    srbit0 = RGB_OFFSET(srcfmt->p.rgb.red);
    sgbits = RGB_SIZE(srcfmt->p.rgb.green);
    sgbit0 = RGB_OFFSET(srcfmt->p.rgb.green);
    sbbits = RGB_SIZE(srcfmt->p.rgb.blue);
    sbbit0 = RGB_OFFSET(srcfmt->p.rgb.blue);

    srcl = src->width * srcfmt->p.rgb.bpp;
    for(y = 0; y < dst->height; y++) {
        if(y >= src->height)
            y -= srcl;
        for(x = 0; x < dst->width; x++) {
            if(x < src->width) {
                uint8_t r, g, b;
                p = convert_read_rgb(srcp, srcfmt->p.rgb.bpp);
                srcp += srcfmt->p.rgb.bpp;

                /* FIXME endianness? */
                r = (p >> srbit0) << srbits;
                g = (p >> sgbit0) << sgbits;
                b = (p >> sbbit0) << sbbits;

                p = (((r >> drbits) << drbit0) |
                     ((g >> dgbits) << dgbit0) |
                     ((b >> dbbits) << dbbit0));
            }
            convert_write_rgb(dstp, p, dstfmt->p.rgb.bpp);
            dstp += dstfmt->p.rgb.bpp;
        }
        if(x < src->width)
            srcp += (src->width - x) * srcfmt->p.rgb.bpp;
    }
}