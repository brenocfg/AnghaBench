#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char* buf; TYPE_2__* avctx; TYPE_1__* frame; } ;
struct TYPE_6__ {int width; int height; } ;
struct TYPE_5__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_3__ Msvideo1Context ;

/* Variables and functions */
 unsigned short AV_RL16 (unsigned char*) ; 
 int /*<<< orphan*/  CHECK_STREAM_PTR (int) ; 

__attribute__((used)) static void msvideo1_decode_16bit(Msvideo1Context *s)
{
    int block_ptr, pixel_ptr;
    int total_blocks;
    int pixel_x, pixel_y;  /* pixel width and height iterators */
    int block_x, block_y;  /* block width and height iterators */
    int blocks_wide, blocks_high;  /* width and height in 4x4 blocks */
    int block_inc;
    int row_dec;

    /* decoding parameters */
    int stream_ptr;
    unsigned char byte_a, byte_b;
    unsigned short flags;
    int skip_blocks;
    unsigned short colors[8];
    unsigned short *pixels = (unsigned short *)s->frame->data[0];
    int stride = s->frame->linesize[0] / 2;

    stream_ptr = 0;
    skip_blocks = 0;
    blocks_wide = s->avctx->width / 4;
    blocks_high = s->avctx->height / 4;
    total_blocks = blocks_wide * blocks_high;
    block_inc = 4;
    row_dec = stride + 4;

    for (block_y = blocks_high; block_y > 0; block_y--) {
        block_ptr = ((block_y * 4) - 1) * stride;
        for (block_x = blocks_wide; block_x > 0; block_x--) {
            /* check if this block should be skipped */
            if (skip_blocks) {
                block_ptr += block_inc;
                skip_blocks--;
                total_blocks--;
                continue;
            }

            pixel_ptr = block_ptr;

            /* get the next two bytes in the encoded data stream */
            CHECK_STREAM_PTR(2);
            byte_a = s->buf[stream_ptr++];
            byte_b = s->buf[stream_ptr++];

            /* check if the decode is finished */
            if ((byte_a == 0) && (byte_b == 0) && (total_blocks == 0)) {
                return;
            } else if ((byte_b & 0xFC) == 0x84) {
                /* skip code, but don't count the current block */
                skip_blocks = ((byte_b - 0x84) << 8) + byte_a - 1;
            } else if (byte_b < 0x80) {
                /* 2- or 8-color encoding modes */
                flags = (byte_b << 8) | byte_a;

                CHECK_STREAM_PTR(4);
                colors[0] = AV_RL16(&s->buf[stream_ptr]);
                stream_ptr += 2;
                colors[1] = AV_RL16(&s->buf[stream_ptr]);
                stream_ptr += 2;

                if (colors[0] & 0x8000) {
                    /* 8-color encoding */
                    CHECK_STREAM_PTR(12);
                    colors[2] = AV_RL16(&s->buf[stream_ptr]);
                    stream_ptr += 2;
                    colors[3] = AV_RL16(&s->buf[stream_ptr]);
                    stream_ptr += 2;
                    colors[4] = AV_RL16(&s->buf[stream_ptr]);
                    stream_ptr += 2;
                    colors[5] = AV_RL16(&s->buf[stream_ptr]);
                    stream_ptr += 2;
                    colors[6] = AV_RL16(&s->buf[stream_ptr]);
                    stream_ptr += 2;
                    colors[7] = AV_RL16(&s->buf[stream_ptr]);
                    stream_ptr += 2;

                    for (pixel_y = 0; pixel_y < 4; pixel_y++) {
                        for (pixel_x = 0; pixel_x < 4; pixel_x++, flags >>= 1)
                            pixels[pixel_ptr++] =
                                colors[((pixel_y & 0x2) << 1) +
                                    (pixel_x & 0x2) + ((flags & 0x1) ^ 1)];
                        pixel_ptr -= row_dec;
                    }
                } else {
                    /* 2-color encoding */
                    for (pixel_y = 0; pixel_y < 4; pixel_y++) {
                        for (pixel_x = 0; pixel_x < 4; pixel_x++, flags >>= 1)
                            pixels[pixel_ptr++] = colors[(flags & 0x1) ^ 1];
                        pixel_ptr -= row_dec;
                    }
                }
            } else {
                /* otherwise, it's a 1-color block */
                colors[0] = (byte_b << 8) | byte_a;

                for (pixel_y = 0; pixel_y < 4; pixel_y++) {
                    for (pixel_x = 0; pixel_x < 4; pixel_x++)
                        pixels[pixel_ptr++] = colors[0];
                    pixel_ptr -= row_dec;
                }
            }

            block_ptr += block_inc;
            total_blocks--;
        }
    }
}