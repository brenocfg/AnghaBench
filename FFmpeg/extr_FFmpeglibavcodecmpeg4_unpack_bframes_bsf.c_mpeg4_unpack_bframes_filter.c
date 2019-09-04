#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_2__* b_frame; } ;
typedef  TYPE_1__ UnpackBFramesBSFContext ;
struct TYPE_20__ {TYPE_1__* priv_data; } ;
struct TYPE_19__ {char* data; scalar_t__ size; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ MAX_NVOP_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_packet_copy_props (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_free (TYPE_2__**) ; 
 int av_packet_make_writable (TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_move_ref (TYPE_2__*,TYPE_2__*) ; 
 int av_packet_ref (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 int ff_bsf_get_packet (TYPE_3__*,TYPE_2__**) ; 
 int /*<<< orphan*/  scan_buffer (char*,scalar_t__,int*,int*,int*) ; 

__attribute__((used)) static int mpeg4_unpack_bframes_filter(AVBSFContext *ctx, AVPacket *out)
{
    UnpackBFramesBSFContext *s = ctx->priv_data;
    int pos_p = -1, nb_vop = 0, pos_vop2 = -1, ret = 0;
    AVPacket *in;

    ret = ff_bsf_get_packet(ctx, &in);
    if (ret < 0)
        return ret;

    scan_buffer(in->data, in->size, &pos_p, &nb_vop, &pos_vop2);
    av_log(ctx, AV_LOG_DEBUG, "Found %d VOP startcode(s) in this packet.\n", nb_vop);

    if (pos_vop2 >= 0) {
        if (s->b_frame->data) {
            av_log(ctx, AV_LOG_WARNING,
                   "Missing one N-VOP packet, discarding one B-frame.\n");
            av_packet_unref(s->b_frame);
        }
        /* store the packed B-frame in the BSFContext */
        ret = av_packet_ref(s->b_frame, in);
        if (ret < 0) {
            goto fail;
        }
        s->b_frame->size -= pos_vop2;
        s->b_frame->data += pos_vop2;
    }

    if (nb_vop > 2) {
        av_log(ctx, AV_LOG_WARNING,
       "Found %d VOP headers in one packet, only unpacking one.\n", nb_vop);
    }

    if (nb_vop == 1 && s->b_frame->data) {
        /* use frame from BSFContext */
        av_packet_move_ref(out, s->b_frame);

        /* use properties from current input packet */
        ret = av_packet_copy_props(out, in);
        if (ret < 0) {
            goto fail;
        }

        if (in->size <= MAX_NVOP_SIZE) {
            /* N-VOP */
            av_log(ctx, AV_LOG_DEBUG, "Skipping N-VOP.\n");
        } else {
            /* copy packet into BSFContext */
            av_packet_move_ref(s->b_frame, in);
        }
    } else if (nb_vop >= 2) {
        /* use first frame of the packet */
        av_packet_move_ref(out, in);
        out->size = pos_vop2;
    } else if (pos_p >= 0) {
        ret = av_packet_make_writable(in);
        if (ret < 0)
            goto fail;
        av_log(ctx, AV_LOG_DEBUG, "Updating DivX userdata (remove trailing 'p').\n");
        av_packet_move_ref(out, in);
        /* remove 'p' (packed) from the end of the (DivX) userdata string */
        out->data[pos_p] = '\0';
    } else {
        /* copy packet */
        av_packet_move_ref(out, in);
    }

fail:
    if (ret < 0)
        av_packet_unref(out);
    av_packet_free(&in);

    return ret;
}