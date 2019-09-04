#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* idct ) (int*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* clear_blocks ) (int*) ;} ;
struct TYPE_8__ {int* prev_dc; int** block; TYPE_2__ idsp; TYPE_1__ bdsp; int /*<<< orphan*/  buf; } ;
typedef  TYPE_3__ JPGContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int FFALIGN (int,int) ; 
 int av_reallocp (int /*<<< orphan*/ *,scalar_t__) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int jpg_decode_block (TYPE_3__*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  jpg_unescape (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int*) ; 
 int /*<<< orphan*/  stub2 (int*) ; 
 int /*<<< orphan*/  stub3 (int*) ; 
 int /*<<< orphan*/  yuv2rgb (int /*<<< orphan*/ *,int const,int,int,int) ; 

__attribute__((used)) static int jpg_decode_data(JPGContext *c, int width, int height,
                           const uint8_t *src, int src_size,
                           uint8_t *dst, int dst_stride,
                           const uint8_t *mask, int mask_stride, int num_mbs,
                           int swapuv)
{
    GetBitContext gb;
    int mb_w, mb_h, mb_x, mb_y, i, j;
    int bx, by;
    int unesc_size;
    int ret;
    const int ridx = swapuv ? 2 : 0;

    if ((ret = av_reallocp(&c->buf,
                           src_size + AV_INPUT_BUFFER_PADDING_SIZE)) < 0)
        return ret;
    jpg_unescape(src, src_size, c->buf, &unesc_size);
    memset(c->buf + unesc_size, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    if((ret = init_get_bits8(&gb, c->buf, unesc_size)) < 0)
        return ret;

    width = FFALIGN(width, 16);
    mb_w  =  width        >> 4;
    mb_h  = (height + 15) >> 4;

    if (!num_mbs)
        num_mbs = mb_w * mb_h * 4;

    for (i = 0; i < 3; i++)
        c->prev_dc[i] = 1024;
    bx =
    by = 0;
    c->bdsp.clear_blocks(c->block[0]);
    for (mb_y = 0; mb_y < mb_h; mb_y++) {
        for (mb_x = 0; mb_x < mb_w; mb_x++) {
            if (mask && !mask[mb_x * 2] && !mask[mb_x * 2 + 1] &&
                !mask[mb_x * 2 +     mask_stride] &&
                !mask[mb_x * 2 + 1 + mask_stride]) {
                bx += 16;
                continue;
            }
            for (j = 0; j < 2; j++) {
                for (i = 0; i < 2; i++) {
                    if (mask && !mask[mb_x * 2 + i + j * mask_stride])
                        continue;
                    num_mbs--;
                    if ((ret = jpg_decode_block(c, &gb, 0,
                                                c->block[i + j * 2])) != 0)
                        return ret;
                    c->idsp.idct(c->block[i + j * 2]);
                }
            }
            for (i = 1; i < 3; i++) {
                if ((ret = jpg_decode_block(c, &gb, i, c->block[i + 3])) != 0)
                    return ret;
                c->idsp.idct(c->block[i + 3]);
            }

            for (j = 0; j < 16; j++) {
                uint8_t *out = dst + bx * 3 + (by + j) * dst_stride;
                for (i = 0; i < 16; i++) {
                    int Y, U, V;

                    Y = c->block[(j >> 3) * 2 + (i >> 3)][(i & 7) + (j & 7) * 8];
                    U = c->block[4][(i >> 1) + (j >> 1) * 8] - 128;
                    V = c->block[5][(i >> 1) + (j >> 1) * 8] - 128;
                    yuv2rgb(out + i * 3, ridx, Y, U, V);
                }
            }

            if (!num_mbs)
                return 0;
            bx += 16;
        }
        bx  = 0;
        by += 16;
        if (mask)
            mask += mask_stride * 2;
    }

    return 0;
}