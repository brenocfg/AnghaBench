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
struct TYPE_13__ {int packorder; unsigned int xsub2; } ;
struct TYPE_14__ {TYPE_1__ yuv; } ;
struct TYPE_16__ {TYPE_2__ p; } ;
typedef  TYPE_4__ zbar_format_def_t ;
typedef  int uint8_t ;

/* Variables and functions */
 int* malloc (unsigned long) ; 
 int /*<<< orphan*/  memset (int*,int,unsigned long) ; 
 int /*<<< orphan*/  uv_roundup (TYPE_3__*,TYPE_4__ const*) ; 
 int uvp_size (TYPE_3__*,TYPE_4__ const*) ; 

__attribute__((used)) static void convert_yuv_unpack (zbar_image_t *dst,
                                const zbar_format_def_t *dstfmt,
                                const zbar_image_t *src,
                                const zbar_format_def_t *srcfmt)
{
    unsigned long dstn, dstm2;
    uint8_t *dsty, flags;
    const uint8_t *srcp;
    unsigned srcl, x, y;
    uint8_t y0 = 0, y1 = 0;

    uv_roundup(dst, dstfmt);
    dstn = dst->width * dst->height;
    dstm2 = uvp_size(dst, dstfmt) * 2;
    dst->datalen = dstn + dstm2;
    dst->data = malloc(dst->datalen);
    if(!dst->data) return;
    if(dstm2)
        memset((uint8_t*)dst->data + dstn, 0x80, dstm2);
    dsty = (uint8_t*)dst->data;

    flags = srcfmt->p.yuv.packorder ^ dstfmt->p.yuv.packorder;
    flags &= 2;
    srcp = src->data;
    if(flags)
        srcp++;

    srcl = src->width + (src->width >> srcfmt->p.yuv.xsub2);
    for(y = 0; y < dst->height; y++) {
        if(y >= src->height)
            srcp -= srcl;
        for(x = 0; x < dst->width; x += 2) {
            if(x < src->width) {
                y0 = *(srcp++);  srcp++;
                y1 = *(srcp++);  srcp++;
            }
            *(dsty++) = y0;
            *(dsty++) = y1;
        }
        if(x < src->width)
            srcp += (src->width - x) * 2;
    }
}