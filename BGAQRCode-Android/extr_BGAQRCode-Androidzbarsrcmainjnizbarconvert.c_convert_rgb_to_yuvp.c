#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {unsigned long width; unsigned long height; unsigned long datalen; int* data; } ;
typedef  TYPE_3__ zbar_image_t ;
struct TYPE_13__ {int bpp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_14__ {TYPE_1__ rgb; } ;
struct TYPE_16__ {TYPE_2__ p; } ;
typedef  TYPE_4__ zbar_format_def_t ;
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int RGB_OFFSET (int /*<<< orphan*/ ) ; 
 int RGB_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int convert_read_rgb (int const*,unsigned int) ; 
 int* malloc (unsigned long) ; 
 int /*<<< orphan*/  memset (int*,int,unsigned long) ; 
 int /*<<< orphan*/  uv_roundup (TYPE_3__*,TYPE_4__ const*) ; 
 int uvp_size (TYPE_3__*,TYPE_4__ const*) ; 

__attribute__((used)) static void convert_rgb_to_yuvp (zbar_image_t *dst,
                                 const zbar_format_def_t *dstfmt,
                                 const zbar_image_t *src,
                                 const zbar_format_def_t *srcfmt)
{
    unsigned long dstn, dstm2;
    uint8_t *dsty;
    const uint8_t *srcp;
    int rbits, rbit0, gbits, gbit0, bbits, bbit0;
    unsigned srcl, x, y;
    uint16_t y0 = 0;

    uv_roundup(dst, dstfmt);
    dstn = dst->width * dst->height;
    dstm2 = uvp_size(dst, dstfmt) * 2;
    dst->datalen = dstn + dstm2;
    dst->data = malloc(dst->datalen);
    if(!dst->data) return;
    if(dstm2)
        memset((uint8_t*)dst->data + dstn, 0x80, dstm2);
    dsty = (void*)dst->data;

    assert(src->datalen >= (src->width * src->height * srcfmt->p.rgb.bpp));
    srcp = src->data;

    rbits = RGB_SIZE(srcfmt->p.rgb.red);
    rbit0 = RGB_OFFSET(srcfmt->p.rgb.red);
    gbits = RGB_SIZE(srcfmt->p.rgb.green);
    gbit0 = RGB_OFFSET(srcfmt->p.rgb.green);
    bbits = RGB_SIZE(srcfmt->p.rgb.blue);
    bbit0 = RGB_OFFSET(srcfmt->p.rgb.blue);

    srcl = src->width * srcfmt->p.rgb.bpp;
    for(y = 0; y < dst->height; y++) {
        if(y >= src->height)
            srcp -= srcl;
        for(x = 0; x < dst->width; x++) {
            if(x < src->width) {
                uint8_t r, g, b;
                uint32_t p = convert_read_rgb(srcp, srcfmt->p.rgb.bpp);
                srcp += srcfmt->p.rgb.bpp;

                /* FIXME endianness? */
                r = ((p >> rbit0) << rbits) & 0xff;
                g = ((p >> gbit0) << gbits) & 0xff;
                b = ((p >> bbit0) << bbits) & 0xff;

                /* FIXME color space? */
                y0 = ((77 * r + 150 * g + 29 * b) + 0x80) >> 8;
            }
            *(dsty++) = y0;
        }
        if(x < src->width)
            srcp += (src->width - x) * srcfmt->p.rgb.bpp;
    }
}