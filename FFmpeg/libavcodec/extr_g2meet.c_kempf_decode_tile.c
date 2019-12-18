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
typedef  int uint8_t ;
typedef  int uLongf ;
struct TYPE_3__ {int tile_width; int tile_height; int* framebuf; int framebuf_stride; int width; int height; int* kempf_flags; int* jpeg_tile; int tile_stride; int /*<<< orphan*/  kempf_buf; int /*<<< orphan*/  jc; } ;
typedef  TYPE_1__ G2MContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int FFALIGN (int,int) ; 
 int FFMIN (int,int) ; 
 int jpg_decode_data (int /*<<< orphan*/ *,int,int,int const*,int,int*,int,int*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kempf_restore_buf (int /*<<< orphan*/ ,int,int*,int,int*,int,int,int,int*,int,int) ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int uncompress (int /*<<< orphan*/ ,int*,int const*,int) ; 

__attribute__((used)) static int kempf_decode_tile(G2MContext *c, int tile_x, int tile_y,
                             const uint8_t *src, int src_size)
{
    int width, height;
    int hdr, zsize, npal, tidx = -1, ret;
    int i, j;
    const uint8_t *src_end = src + src_size;
    uint8_t pal[768], transp[3];
    uLongf dlen = (c->tile_width + 1) * c->tile_height;
    int sub_type;
    int nblocks, cblocks, bstride;
    int bits, bitbuf, coded;
    uint8_t *dst = c->framebuf + tile_x * c->tile_width * 3 +
                   tile_y * c->tile_height * c->framebuf_stride;

    if (src_size < 2)
        return AVERROR_INVALIDDATA;

    width  = FFMIN(c->width  - tile_x * c->tile_width,  c->tile_width);
    height = FFMIN(c->height - tile_y * c->tile_height, c->tile_height);

    hdr      = *src++;
    sub_type = hdr >> 5;
    if (sub_type == 0) {
        int j;
        memcpy(transp, src, 3);
        src += 3;
        for (j = 0; j < height; j++, dst += c->framebuf_stride)
            for (i = 0; i < width; i++)
                memcpy(dst + i * 3, transp, 3);
        return 0;
    } else if (sub_type == 1) {
        return jpg_decode_data(&c->jc, width, height, src, src_end - src,
                               dst, c->framebuf_stride, NULL, 0, 0, 0);
    }

    if (sub_type != 2) {
        memcpy(transp, src, 3);
        src += 3;
    }
    npal = *src++ + 1;
    if (src_end - src < npal * 3)
        return AVERROR_INVALIDDATA;
    memcpy(pal, src, npal * 3);
    src += npal * 3;
    if (sub_type != 2) {
        for (i = 0; i < npal; i++) {
            if (!memcmp(pal + i * 3, transp, 3)) {
                tidx = i;
                break;
            }
        }
    }

    if (src_end - src < 2)
        return 0;
    zsize = (src[0] << 8) | src[1];
    src  += 2;

    if (src_end - src < zsize + (sub_type != 2))
        return AVERROR_INVALIDDATA;

    ret = uncompress(c->kempf_buf, &dlen, src, zsize);
    if (ret)
        return AVERROR_INVALIDDATA;
    src += zsize;

    if (sub_type == 2) {
        kempf_restore_buf(c->kempf_buf, dlen, dst, c->framebuf_stride,
                          NULL, 0, width, height, pal, npal, tidx);
        return 0;
    }

    nblocks = *src++ + 1;
    cblocks = 0;
    bstride = FFALIGN(width, 16) >> 3;
    // blocks are coded LSB and we need normal bitreader for JPEG data
    bits = 0;
    for (i = 0; i < (FFALIGN(height, 16) >> 4); i++) {
        for (j = 0; j < (FFALIGN(width, 16) >> 4); j++) {
            if (!bits) {
                if (src >= src_end)
                    return AVERROR_INVALIDDATA;
                bitbuf = *src++;
                bits   = 8;
            }
            coded = bitbuf & 1;
            bits--;
            bitbuf >>= 1;
            cblocks += coded;
            if (cblocks > nblocks)
                return AVERROR_INVALIDDATA;
            c->kempf_flags[j * 2 +      i * 2      * bstride] =
            c->kempf_flags[j * 2 + 1 +  i * 2      * bstride] =
            c->kempf_flags[j * 2 +     (i * 2 + 1) * bstride] =
            c->kempf_flags[j * 2 + 1 + (i * 2 + 1) * bstride] = coded;
        }
    }

    memset(c->jpeg_tile, 0, c->tile_stride * height);
    jpg_decode_data(&c->jc, width, height, src, src_end - src,
                    c->jpeg_tile, c->tile_stride,
                    c->kempf_flags, bstride, nblocks * 4, 0);

    kempf_restore_buf(c->kempf_buf, dlen, dst, c->framebuf_stride,
                      c->jpeg_tile, c->tile_stride,
                      width, height, pal, npal, tidx);

    return 0;
}