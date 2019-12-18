#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_21__ {TYPE_1__* priv_data; } ;
struct TYPE_20__ {int key_frame; int /*<<< orphan*/ * data; int /*<<< orphan*/  pict_type; } ;
struct TYPE_19__ {int size; scalar_t__ data; } ;
struct TYPE_18__ {int width; int height; int version; int /*<<< orphan*/  palette; int /*<<< orphan*/  current; int /*<<< orphan*/  processed; int /*<<< orphan*/  previous; } ;
typedef  TYPE_1__ Hnm4VideoContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 scalar_t__ AV_RL16 (scalar_t__) ; 
 scalar_t__ HNM4_CHUNK_ID_IU ; 
 scalar_t__ HNM4_CHUNK_ID_IZ ; 
 scalar_t__ HNM4_CHUNK_ID_PL ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  copy_processed_frame (TYPE_4__*,TYPE_3__*) ; 
 int decode_interframe_v4 (TYPE_4__*,scalar_t__,int) ; 
 int /*<<< orphan*/  decode_interframe_v4a (TYPE_4__*,scalar_t__,int) ; 
 int ff_get_buffer (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hnm_flip_buffers (TYPE_1__*) ; 
 int /*<<< orphan*/  hnm_update_palette (TYPE_4__*,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  postprocess_current_frame (TYPE_4__*) ; 
 int /*<<< orphan*/  unpack_intraframe (TYPE_4__*,scalar_t__,int) ; 

__attribute__((used)) static int hnm_decode_frame(AVCodecContext *avctx, void *data,
                            int *got_frame, AVPacket *avpkt)
{
    AVFrame *frame = data;
    Hnm4VideoContext *hnm = avctx->priv_data;
    int ret;
    uint16_t chunk_id;

    if (avpkt->size < 8) {
        av_log(avctx, AV_LOG_ERROR, "packet too small\n");
        return AVERROR_INVALIDDATA;
    }

    chunk_id = AV_RL16(avpkt->data + 4);

    if (chunk_id == HNM4_CHUNK_ID_PL) {
        hnm_update_palette(avctx, avpkt->data, avpkt->size);
    } else if (chunk_id == HNM4_CHUNK_ID_IZ) {
        if (avpkt->size < 12) {
            av_log(avctx, AV_LOG_ERROR, "packet too small\n");
            return AVERROR_INVALIDDATA;
        }
        if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
            return ret;

        unpack_intraframe(avctx, avpkt->data + 12, avpkt->size - 12);
        memcpy(hnm->previous, hnm->current, hnm->width * hnm->height);
        if (hnm->version == 0x4a)
            memcpy(hnm->processed, hnm->current, hnm->width * hnm->height);
        else
            postprocess_current_frame(avctx);
        copy_processed_frame(avctx, frame);
        frame->pict_type = AV_PICTURE_TYPE_I;
        frame->key_frame = 1;
        memcpy(frame->data[1], hnm->palette, 256 * 4);
        *got_frame = 1;
    } else if (chunk_id == HNM4_CHUNK_ID_IU) {
        if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
            return ret;

        if (hnm->version == 0x4a) {
            decode_interframe_v4a(avctx, avpkt->data + 8, avpkt->size - 8);
            memcpy(hnm->processed, hnm->current, hnm->width * hnm->height);
        } else {
            int ret = decode_interframe_v4(avctx, avpkt->data + 8, avpkt->size - 8);
            if (ret < 0)
                return ret;
            postprocess_current_frame(avctx);
        }
        copy_processed_frame(avctx, frame);
        frame->pict_type = AV_PICTURE_TYPE_P;
        frame->key_frame = 0;
        memcpy(frame->data[1], hnm->palette, 256 * 4);
        *got_frame = 1;
        hnm_flip_buffers(hnm);
    } else {
        av_log(avctx, AV_LOG_ERROR, "invalid chunk id: %d\n", chunk_id);
        return AVERROR_INVALIDDATA;
    }

    return avpkt->size;
}