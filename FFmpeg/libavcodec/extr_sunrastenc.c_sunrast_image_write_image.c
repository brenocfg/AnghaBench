#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int width; int height; TYPE_1__* priv_data; } ;
struct TYPE_4__ {int maplength; int depth; scalar_t__ type; int length; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ SUNRASTContext ;
typedef  int /*<<< orphan*/  PutByteContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int GET_VALUE ; 
 int RLE_TRIGGER ; 
 scalar_t__ RT_BYTE_ENCODED ; 
 int /*<<< orphan*/  bytestream2_put_be16u (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_put_buffer (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  bytestream2_put_byteu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_skip_p (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell_p (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sunrast_image_write_image(AVCodecContext *avctx,
                                      const uint8_t *pixels,
                                      const uint32_t *palette_data,
                                      int linesize)
{
    SUNRASTContext *s = avctx->priv_data;
    const uint8_t *ptr;
    int len, alen, x, y;

    if (s->maplength) {     // palettized
        PutByteContext pb_r, pb_g;
        int len = s->maplength / 3;

        pb_r = s->p;
        bytestream2_skip_p(&s->p, len);
        pb_g = s->p;
        bytestream2_skip_p(&s->p, len);

        for (x = 0; x < len; x++) {
            uint32_t pixel = palette_data[x];

            bytestream2_put_byteu(&pb_r, (pixel >> 16) & 0xFF);
            bytestream2_put_byteu(&pb_g, (pixel >> 8)  & 0xFF);
            bytestream2_put_byteu(&s->p,  pixel        & 0xFF);
        }
    }

    len  = (s->depth * avctx->width + 7) >> 3;
    alen = len + (len & 1);
    ptr  = pixels;

     if (s->type == RT_BYTE_ENCODED) {
        uint8_t value, value2;
        int run;

        ptr = pixels;

#define GET_VALUE y >= avctx->height ? 0 : x >= len ? ptr[len-1] : ptr[x]

        x = 0, y = 0;
        value2 = GET_VALUE;
        while (y < avctx->height) {
            run = 1;
            value = value2;
            x++;
            if (x >= alen) {
                x = 0;
                ptr += linesize, y++;
            }

            value2 = GET_VALUE;
            while (value2 == value && run < 256 && y < avctx->height) {
                x++;
                run++;
                if (x >= alen) {
                    x = 0;
                    ptr += linesize, y++;
                }
                value2 = GET_VALUE;
            }

            if (run > 2 || value == RLE_TRIGGER) {
                bytestream2_put_byteu(&s->p, RLE_TRIGGER);
                bytestream2_put_byteu(&s->p, run - 1);
                if (run > 1)
                    bytestream2_put_byteu(&s->p, value);
            } else if (run == 1) {
                bytestream2_put_byteu(&s->p, value);
            } else
                bytestream2_put_be16u(&s->p, (value << 8) | value);
        }

        // update data length for header
        s->length = bytestream2_tell_p(&s->p) - 32 - s->maplength;
    } else {
        for (y = 0; y < avctx->height; y++) {
            bytestream2_put_buffer(&s->p, ptr, len);
            if (len < alen)
                bytestream2_put_byteu(&s->p, 0);
            ptr += linesize;
        }
    }
}