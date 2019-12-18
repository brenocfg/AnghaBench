#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_19__ {TYPE_2__* priv_data; } ;
struct TYPE_18__ {int key_frame; int** data; int* linesize; int /*<<< orphan*/  pict_type; } ;
struct TYPE_17__ {int* data; int size; } ;
struct TYPE_16__ {TYPE_4__* frame; } ;
struct TYPE_15__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ GetBitContext ;
typedef  int AvsVideoSubType ;
typedef  TYPE_2__ AvsContext ;
typedef  int AvsBlockType ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
#define  AVS_I_FRAME 131 
 int AVS_PALETTE ; 
#define  AVS_P_FRAME_2X2 130 
#define  AVS_P_FRAME_2X3 129 
#define  AVS_P_FRAME_3X3 128 
 int AVS_VIDEO ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 int AV_RL16 (int const*) ; 
 int /*<<< orphan*/  align_get_bits (TYPE_1__*) ; 
 int av_frame_ref (TYPE_4__*,TYPE_4__* const) ; 
 int ff_reget_buffer (TYPE_5__*,TYPE_4__* const,int /*<<< orphan*/ ) ; 
 scalar_t__ get_bits1 (TYPE_1__*) ; 
 int /*<<< orphan*/  init_get_bits (TYPE_1__*,int const*,int) ; 

__attribute__((used)) static int
avs_decode_frame(AVCodecContext * avctx,
                 void *data, int *got_frame, AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    const uint8_t *buf_end = avpkt->data + avpkt->size;
    int buf_size = avpkt->size;
    AvsContext *const avs = avctx->priv_data;
    AVFrame *picture = data;
    AVFrame *const p =  avs->frame;
    const uint8_t *table, *vect;
    uint8_t *out;
    int i, j, x, y, stride, ret, vect_w = 3, vect_h = 3;
    AvsVideoSubType sub_type;
    AvsBlockType type;
    GetBitContext change_map = {0}; //init to silence warning

    if ((ret = ff_reget_buffer(avctx, p, 0)) < 0)
        return ret;
    p->pict_type = AV_PICTURE_TYPE_P;
    p->key_frame = 0;

    out    = p->data[0];
    stride = p->linesize[0];

    if (buf_end - buf < 4)
        return AVERROR_INVALIDDATA;
    sub_type = buf[0];
    type = buf[1];
    buf += 4;

    if (type == AVS_PALETTE) {
        int first, last;
        uint32_t *pal = (uint32_t *) p->data[1];

        first = AV_RL16(buf);
        last = first + AV_RL16(buf + 2);
        if (first >= 256 || last > 256 || buf_end - buf < 4 + 4 + 3 * (last - first))
            return AVERROR_INVALIDDATA;
        buf += 4;
        for (i=first; i<last; i++, buf+=3) {
            pal[i] = (buf[0] << 18) | (buf[1] << 10) | (buf[2] << 2);
            pal[i] |= 0xFFU << 24 | (pal[i] >> 6) & 0x30303;
        }

        sub_type = buf[0];
        type = buf[1];
        buf += 4;
    }

    if (type != AVS_VIDEO)
        return AVERROR_INVALIDDATA;

    switch (sub_type) {
    case AVS_I_FRAME:
        p->pict_type = AV_PICTURE_TYPE_I;
        p->key_frame = 1;
    case AVS_P_FRAME_3X3:
        vect_w = 3;
        vect_h = 3;
        break;

    case AVS_P_FRAME_2X2:
        vect_w = 2;
        vect_h = 2;
        break;

    case AVS_P_FRAME_2X3:
        vect_w = 2;
        vect_h = 3;
        break;

    default:
      return AVERROR_INVALIDDATA;
    }

    if (buf_end - buf < 256 * vect_w * vect_h)
        return AVERROR_INVALIDDATA;
    table = buf + (256 * vect_w * vect_h);
    if (sub_type != AVS_I_FRAME) {
        int map_size = ((318 / vect_w + 7) / 8) * (198 / vect_h);
        if (buf_end - table < map_size)
            return AVERROR_INVALIDDATA;
        init_get_bits(&change_map, table, map_size * 8);
        table += map_size;
    }

    for (y=0; y<198; y+=vect_h) {
        for (x=0; x<318; x+=vect_w) {
            if (sub_type == AVS_I_FRAME || get_bits1(&change_map)) {
                if (buf_end - table < 1)
                    return AVERROR_INVALIDDATA;
                vect = &buf[*table++ * (vect_w * vect_h)];
                for (j=0; j<vect_w; j++) {
                    out[(y + 0) * stride + x + j] = vect[(0 * vect_w) + j];
                    out[(y + 1) * stride + x + j] = vect[(1 * vect_w) + j];
                    if (vect_h == 3)
                        out[(y + 2) * stride + x + j] =
                            vect[(2 * vect_w) + j];
                }
            }
        }
        if (sub_type != AVS_I_FRAME)
            align_get_bits(&change_map);
    }

    if ((ret = av_frame_ref(picture, p)) < 0)
        return ret;
    *got_frame = 1;

    return buf_size;
}