#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_18__ {int /*<<< orphan*/  f; } ;
struct TYPE_17__ {int slice_count; int /*<<< orphan*/  frame_number; TYPE_1__* priv_data; } ;
struct TYPE_16__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {scalar_t__ mb_y; scalar_t__ mb_height; scalar_t__ pict_type; TYPE_9__* current_picture_ptr; scalar_t__ low_delay; TYPE_9__* last_picture_ptr; int /*<<< orphan*/  er; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PICTURE_TYPE_B ; 
 unsigned int FFMAX (int,int) ; 
 int /*<<< orphan*/  FF_QSCALE_TYPE_MPEG1 ; 
 int av_frame_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_3__*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_er_frame_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_mpv_export_qp_table (TYPE_1__*,int /*<<< orphan*/ *,TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_mpv_frame_end (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_print_debug_info (TYPE_1__*,TYPE_9__*,int /*<<< orphan*/ *) ; 
 unsigned int get_slice_offset (TYPE_3__*,int /*<<< orphan*/  const*,int) ; 
 int rv10_decode_packet (TYPE_3__*,int /*<<< orphan*/  const*,int,int,int) ; 

__attribute__((used)) static int rv10_decode_frame(AVCodecContext *avctx, void *data, int *got_frame,
                             AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;
    MpegEncContext *s = avctx->priv_data;
    AVFrame *pict = data;
    int i, ret;
    int slice_count;
    const uint8_t *slices_hdr = NULL;

    ff_dlog(avctx, "*****frame %d size=%d\n", avctx->frame_number, buf_size);

    /* no supplementary picture */
    if (buf_size == 0) {
        return 0;
    }

    if (!avctx->slice_count) {
        slice_count = (*buf++) + 1;
        buf_size--;

        if (!slice_count || buf_size <= 8 * slice_count) {
            av_log(avctx, AV_LOG_ERROR, "Invalid slice count: %d.\n",
                   slice_count);
            return AVERROR_INVALIDDATA;
        }

        slices_hdr = buf + 4;
        buf       += 8 * slice_count;
        buf_size  -= 8 * slice_count;
    } else
        slice_count = avctx->slice_count;

    for (i = 0; i < slice_count; i++) {
        unsigned offset = get_slice_offset(avctx, slices_hdr, i);
        int size, size2;

        if (offset >= buf_size)
            return AVERROR_INVALIDDATA;

        if (i + 1 == slice_count)
            size = buf_size - offset;
        else
            size = get_slice_offset(avctx, slices_hdr, i + 1) - offset;

        if (i + 2 >= slice_count)
            size2 = buf_size - offset;
        else
            size2 = get_slice_offset(avctx, slices_hdr, i + 2) - offset;

        if (size <= 0 || size2 <= 0 ||
            offset + FFMAX(size, size2) > buf_size)
            return AVERROR_INVALIDDATA;

        if ((ret = rv10_decode_packet(avctx, buf + offset, size, size2, buf_size)) < 0)
            return ret;

        if (ret > 8 * size)
            i++;
    }

    if (s->current_picture_ptr && s->mb_y >= s->mb_height) {
        ff_er_frame_end(&s->er);
        ff_mpv_frame_end(s);

        if (s->pict_type == AV_PICTURE_TYPE_B || s->low_delay) {
            if ((ret = av_frame_ref(pict, s->current_picture_ptr->f)) < 0)
                return ret;
            ff_print_debug_info(s, s->current_picture_ptr, pict);
            ff_mpv_export_qp_table(s, pict, s->current_picture_ptr, FF_QSCALE_TYPE_MPEG1);
        } else if (s->last_picture_ptr) {
            if ((ret = av_frame_ref(pict, s->last_picture_ptr->f)) < 0)
                return ret;
            ff_print_debug_info(s, s->last_picture_ptr, pict);
            ff_mpv_export_qp_table(s, pict,s->last_picture_ptr, FF_QSCALE_TYPE_MPEG1);
        }

        if (s->last_picture_ptr || s->low_delay) {
            *got_frame = 1;
        }

        // so we can detect if frame_end was not called (find some nicer solution...)
        s->current_picture_ptr = NULL;
    }

    return avpkt->size;
}