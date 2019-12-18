#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_17__ {TYPE_1__* priv_data; } ;
struct TYPE_16__ {int* linesize; int key_frame; int palette_has_changed; int /*<<< orphan*/ ** data; int /*<<< orphan*/  pict_type; } ;
struct TYPE_15__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_14__ {size_t currentpic; TYPE_3__** pictures; } ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_1__ C93DecoderContext ;
typedef  int C93BlockType ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
#define  C93_4X4_2COLOR 136 
#define  C93_4X4_4COLOR 135 
#define  C93_4X4_4COLOR_GRP 134 
#define  C93_4X4_FROM_CURR 133 
#define  C93_4X4_FROM_PREV 132 
#define  C93_8X8_2COLOR 131 
#define  C93_8X8_FROM_PREV 130 
#define  C93_8X8_INTRA 129 
 int C93_FIRST_FRAME ; 
 int C93_HAS_PALETTE ; 
#define  C93_NOOP 128 
 int FFABS (int) ; 
 int HEIGHT ; 
 int WIDTH ; 
 int av_frame_ref (void*,TYPE_3__* const) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_4__*,char*,int,int,int,int) ; 
 int bytestream2_get_be24 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_get_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 void* bytestream2_get_le16 (int /*<<< orphan*/ *) ; 
 void* bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int copy_block (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  draw_n_color (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int ff_reget_buffer (TYPE_4__*,TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int ff_set_dimensions (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_frame(AVCodecContext *avctx, void *data,
                        int *got_frame, AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    C93DecoderContext * const c93 = avctx->priv_data;
    AVFrame * const newpic = c93->pictures[c93->currentpic];
    AVFrame * const oldpic = c93->pictures[c93->currentpic^1];
    GetByteContext gb;
    uint8_t *out;
    int stride, ret, i, x, y, b, bt = 0;

    if ((ret = ff_set_dimensions(avctx, WIDTH, HEIGHT)) < 0)
        return ret;

    c93->currentpic ^= 1;

    if ((ret = ff_reget_buffer(avctx, newpic, 0)) < 0)
        return ret;

    stride = newpic->linesize[0];

    bytestream2_init(&gb, buf, buf_size);
    b = bytestream2_get_byte(&gb);
    if (b & C93_FIRST_FRAME) {
        newpic->pict_type = AV_PICTURE_TYPE_I;
        newpic->key_frame = 1;
    } else {
        newpic->pict_type = AV_PICTURE_TYPE_P;
        newpic->key_frame = 0;
    }

    for (y = 0; y < HEIGHT; y += 8) {
        out = newpic->data[0] + y * stride;
        for (x = 0; x < WIDTH; x += 8) {
            uint8_t *copy_from = oldpic->data[0];
            unsigned int offset, j;
            uint8_t cols[4], grps[4];
            C93BlockType block_type;

            if (!bt)
                bt = bytestream2_get_byte(&gb);

            block_type= bt & 0x0F;
            switch (block_type) {
            case C93_8X8_FROM_PREV:
                offset = bytestream2_get_le16(&gb);
                if ((ret = copy_block(avctx, out, copy_from, offset, 8, stride)) < 0)
                    return ret;
                break;

            case C93_4X4_FROM_CURR:
                copy_from = newpic->data[0];
            case C93_4X4_FROM_PREV:
                for (j = 0; j < 8; j += 4) {
                    for (i = 0; i < 8; i += 4) {
                        int offset = bytestream2_get_le16(&gb);
                        int from_x = offset % WIDTH;
                        int from_y = offset / WIDTH;
                        if (block_type == C93_4X4_FROM_CURR && from_y == y+j &&
                            (FFABS(from_x - x-i) < 4 || FFABS(from_x - x-i) > WIDTH-4)) {
                            avpriv_request_sample(avctx, "block overlap %d %d %d %d", from_x, x+i, from_y, y+j);
                            return AVERROR_INVALIDDATA;
                        }
                        if ((ret = copy_block(avctx, &out[j*stride+i],
                                              copy_from, offset, 4, stride)) < 0)
                            return ret;
                    }
                }
                break;

            case C93_8X8_2COLOR:
                bytestream2_get_buffer(&gb, cols, 2);
                for (i = 0; i < 8; i++) {
                    draw_n_color(out + i*stride, stride, 8, 1, 1, cols,
                                     NULL, bytestream2_get_byte(&gb));
                }

                break;

            case C93_4X4_2COLOR:
            case C93_4X4_4COLOR:
            case C93_4X4_4COLOR_GRP:
                for (j = 0; j < 8; j += 4) {
                    for (i = 0; i < 8; i += 4) {
                        if (block_type == C93_4X4_2COLOR) {
                            bytestream2_get_buffer(&gb, cols, 2);
                            draw_n_color(out + i + j*stride, stride, 4, 4,
                                    1, cols, NULL, bytestream2_get_le16(&gb));
                        } else if (block_type == C93_4X4_4COLOR) {
                            bytestream2_get_buffer(&gb, cols, 4);
                            draw_n_color(out + i + j*stride, stride, 4, 4,
                                    2, cols, NULL, bytestream2_get_le32(&gb));
                        } else {
                            bytestream2_get_buffer(&gb, grps, 4);
                            draw_n_color(out + i + j*stride, stride, 4, 4,
                                    1, cols, grps, bytestream2_get_le16(&gb));
                        }
                    }
                }
                break;

            case C93_NOOP:
                break;

            case C93_8X8_INTRA:
                for (j = 0; j < 8; j++)
                    bytestream2_get_buffer(&gb, out + j*stride, 8);
                break;

            default:
                av_log(avctx, AV_LOG_ERROR, "unexpected type %x at %dx%d\n",
                       block_type, x, y);
                return AVERROR_INVALIDDATA;
            }
            bt >>= 4;
            out += 8;
        }
    }

    if (b & C93_HAS_PALETTE) {
        uint32_t *palette = (uint32_t *) newpic->data[1];
        for (i = 0; i < 256; i++) {
            palette[i] = 0xFFU << 24 | bytestream2_get_be24(&gb);
        }
        newpic->palette_has_changed = 1;
    } else {
        if (oldpic->data[1])
            memcpy(newpic->data[1], oldpic->data[1], 256 * 4);
    }

    if ((ret = av_frame_ref(data, newpic)) < 0)
        return ret;
    *got_frame = 1;

    return buf_size;
}