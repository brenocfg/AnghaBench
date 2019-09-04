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
 int /*<<< orphan*/  uv_roundup (TYPE_3__*,TYPE_4__ const*) ; 
 int uvp_size (TYPE_3__*,TYPE_4__ const*) ; 

__attribute__((used)) static void convert_uv_resample (zbar_image_t *dst,
                                 const zbar_format_def_t *dstfmt,
                                 const zbar_image_t *src,
                                 const zbar_format_def_t *srcfmt)
{
    unsigned long dstn;
    uint8_t *dstp, flags;
    const uint8_t *srcp;
    unsigned srcl, x, y;
    uint8_t y0 = 0, y1 = 0, u = 0x80, v = 0x80;

    uv_roundup(dst, dstfmt);
    dstn = dst->width * dst->height;
    dst->datalen = dstn + uvp_size(dst, dstfmt) * 2;
    dst->data = malloc(dst->datalen);
    if(!dst->data) return;
    dstp = (void*)dst->data;

    flags = (srcfmt->p.yuv.packorder ^ dstfmt->p.yuv.packorder) & 1;
    srcp = src->data;

    srcl = src->width + (src->width >> srcfmt->p.yuv.xsub2);
    for(y = 0; y < dst->height; y++) {
        if(y >= src->height)
            srcp -= srcl;
        for(x = 0; x < dst->width; x += 2) {
            if(x < src->width) {
                if(!(srcfmt->p.yuv.packorder & 2)) {
                    y0 = *(srcp++);  u = *(srcp++);
                    y1 = *(srcp++);  v = *(srcp++);
                }
                else {
                    u = *(srcp++);  y0 = *(srcp++);
                    v = *(srcp++);  y1 = *(srcp++);
                }
                if(flags) {
                    uint8_t tmp = u;  u = v;  v = tmp;
                }
            }
            if(!(dstfmt->p.yuv.packorder & 2)) {
                *(dstp++) = y0;  *(dstp++) = u;
                *(dstp++) = y1;  *(dstp++) = v;
            }
            else {
                *(dstp++) = u;  *(dstp++) = y0;
                *(dstp++) = v;  *(dstp++) = y1;
            }
        }
        if(x < src->width)
            srcp += (src->width - x) * 2;
    }
}