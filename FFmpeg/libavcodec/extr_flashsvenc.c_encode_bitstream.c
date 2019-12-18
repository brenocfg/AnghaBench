#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {int image_width; int image_height; int /*<<< orphan*/  avctx; int /*<<< orphan*/  tmpblock; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ FlashSVContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int Z_OK ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  bytestream_put_be16 (int /*<<< orphan*/ **,unsigned long) ; 
 int compress2 (int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ ,int,int) ; 
 int copy_region_enc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_dlog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int encode_bitstream(FlashSVContext *s, const AVFrame *p, uint8_t *buf,
                            int buf_size, int block_width, int block_height,
                            uint8_t *previous_frame, int *I_frame)
{

    PutBitContext pb;
    int h_blocks, v_blocks, h_part, v_part, i, j;
    int buf_pos, res;
    int pred_blocks = 0;

    init_put_bits(&pb, buf, buf_size);

    put_bits(&pb,  4, block_width / 16 - 1);
    put_bits(&pb, 12, s->image_width);
    put_bits(&pb,  4, block_height / 16 - 1);
    put_bits(&pb, 12, s->image_height);
    flush_put_bits(&pb);
    buf_pos = 4;

    h_blocks = s->image_width  / block_width;
    h_part   = s->image_width  % block_width;
    v_blocks = s->image_height / block_height;
    v_part   = s->image_height % block_height;

    /* loop over all block columns */
    for (j = 0; j < v_blocks + (v_part ? 1 : 0); j++) {

        int y_pos = j * block_height; // vertical position in frame
        int cur_blk_height = (j < v_blocks) ? block_height : v_part;

        /* loop over all block rows */
        for (i = 0; i < h_blocks + (h_part ? 1 : 0); i++) {
            int x_pos = i * block_width; // horizontal position in frame
            int cur_blk_width = (i < h_blocks) ? block_width : h_part;
            int ret = Z_OK;
            uint8_t *ptr = buf + buf_pos;

            /* copy the block to the temp buffer before compression
             * (if it differs from the previous frame's block) */
            res = copy_region_enc(p->data[0], s->tmpblock,
                                  s->image_height - (y_pos + cur_blk_height + 1),
                                  x_pos, cur_blk_height, cur_blk_width,
                                  p->linesize[0], previous_frame);

            if (res || *I_frame) {
                unsigned long zsize = 3 * block_width * block_height;
                ret = compress2(ptr + 2, &zsize, s->tmpblock,
                                3 * cur_blk_width * cur_blk_height, 9);

                //ret = deflateReset(&s->zstream);
                if (ret != Z_OK)
                    av_log(s->avctx, AV_LOG_ERROR,
                           "error while compressing block %dx%d\n", i, j);

                bytestream_put_be16(&ptr, zsize);
                buf_pos += zsize + 2;
                ff_dlog(s->avctx, "buf_pos = %d\n", buf_pos);
            } else {
                pred_blocks++;
                bytestream_put_be16(&ptr, 0);
                buf_pos += 2;
            }
        }
    }

    if (pred_blocks)
        *I_frame = 0;
    else
        *I_frame = 1;

    return buf_pos;
}