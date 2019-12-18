#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* b_frame_ref; } ;
typedef  TYPE_1__ UnpackBFramesBSFContext ;
struct TYPE_18__ {TYPE_1__* priv_data; } ;
struct TYPE_17__ {char* data; int size; } ;
struct TYPE_16__ {char* data; int size; TYPE_3__* buf; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVBufferRef ;
typedef  TYPE_4__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ MAX_NVOP_SIZE ; 
 TYPE_3__* av_buffer_ref (TYPE_3__*) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_3__**) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_packet_make_writable (TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 int ff_bsf_get_packet_ref (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  scan_buffer (char*,int,int*,int*,int*) ; 

__attribute__((used)) static int mpeg4_unpack_bframes_filter(AVBSFContext *ctx, AVPacket *pkt)
{
    UnpackBFramesBSFContext *s = ctx->priv_data;
    int pos_p = -1, nb_vop = 0, pos_vop2 = -1, ret = 0;

    ret = ff_bsf_get_packet_ref(ctx, pkt);
    if (ret < 0)
        return ret;

    scan_buffer(pkt->data, pkt->size, &pos_p, &nb_vop, &pos_vop2);
    av_log(ctx, AV_LOG_DEBUG, "Found %d VOP startcode(s) in this packet.\n", nb_vop);

    if (pos_vop2 >= 0) {
        if (s->b_frame_ref) {
            av_log(ctx, AV_LOG_WARNING,
                   "Missing one N-VOP packet, discarding one B-frame.\n");
            av_buffer_unref(&s->b_frame_ref);
        }
        /* store a reference to the packed B-frame's data in the BSFContext */
        s->b_frame_ref = av_buffer_ref(pkt->buf);
        if (!s->b_frame_ref) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        s->b_frame_ref->data = pkt->data + pos_vop2;
        s->b_frame_ref->size = pkt->size - pos_vop2;
    }

    if (nb_vop > 2) {
        av_log(ctx, AV_LOG_WARNING,
       "Found %d VOP headers in one packet, only unpacking one.\n", nb_vop);
    }

    if (nb_vop == 1 && s->b_frame_ref) {
        AVBufferRef *tmp = pkt->buf;

        /* make tmp accurately reflect the packet's data */
        tmp->data = pkt->data;
        tmp->size = pkt->size;

        /* replace data in packet with stored data */
        pkt->buf  = s->b_frame_ref;
        pkt->data = s->b_frame_ref->data;
        pkt->size = s->b_frame_ref->size;

        /* store reference to data into BSFContext */
        s->b_frame_ref = tmp;

        if (s->b_frame_ref->size <= MAX_NVOP_SIZE) {
            /* N-VOP - discard stored data */
            av_log(ctx, AV_LOG_DEBUG, "Skipping N-VOP.\n");
            av_buffer_unref(&s->b_frame_ref);
        }
    } else if (nb_vop >= 2) {
        /* use first frame of the packet */
        pkt->size = pos_vop2;
    } else if (pos_p >= 0) {
        ret = av_packet_make_writable(pkt);
        if (ret < 0)
            goto fail;
        av_log(ctx, AV_LOG_DEBUG, "Updating DivX userdata (remove trailing 'p').\n");
        /* remove 'p' (packed) from the end of the (DivX) userdata string */
        pkt->data[pos_p] = '\0';
    } else {
        /* use packet as is */
    }

fail:
    if (ret < 0)
        av_packet_unref(pkt);

    return ret;
}