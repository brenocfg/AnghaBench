#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_34__ {int tg_end; } ;
struct TYPE_25__ {int tile_cols; int tile_rows; int /*<<< orphan*/  show_frame; scalar_t__ show_existing_frame; } ;
struct TYPE_27__ {TYPE_10__ header; } ;
struct TYPE_29__ {TYPE_8__ tile_group; TYPE_10__ frame_header; TYPE_1__ frame; } ;
struct TYPE_28__ {int obu_type; } ;
struct TYPE_35__ {TYPE_3__ obu; TYPE_2__ header; } ;
struct TYPE_33__ {TYPE_11__* priv_data; } ;
struct TYPE_32__ {int size; int /*<<< orphan*/  pts; int /*<<< orphan*/ * data; } ;
struct TYPE_31__ {int nb_units; TYPE_4__* units; } ;
struct TYPE_30__ {scalar_t__ type; scalar_t__ data; TYPE_9__* content; scalar_t__ data_size; } ;
struct TYPE_26__ {scalar_t__ cur_frame; int cur_frame_idx; int last_frame_idx; int nb_frames; int /*<<< orphan*/  cbc; TYPE_6__* buffer_pkt; TYPE_5__ temporal_unit; } ;
typedef  TYPE_4__ CodedBitstreamUnit ;
typedef  TYPE_5__ CodedBitstreamFragment ;
typedef  TYPE_6__ AVPacket ;
typedef  TYPE_7__ AVBSFContext ;
typedef  TYPE_8__ AV1RawTileGroup ;
typedef  TYPE_9__ AV1RawOBU ;
typedef  TYPE_10__ AV1RawFrameHeader ;
typedef  TYPE_11__ AV1FSplitContext ;

/* Variables and functions */
 scalar_t__ AV1_OBU_FRAME ; 
 int AV1_OBU_FRAME_HEADER ; 
 scalar_t__ AV1_OBU_TILE_GROUP ; 
 scalar_t__ AV1_OBU_TILE_LIST ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_packet_move_ref (TYPE_6__*,TYPE_6__*) ; 
 int av_packet_ref (TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_6__*) ; 
 int ff_bsf_get_packet_ref (TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ff_cbs_fragment_reset (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int ff_cbs_read_packet (int /*<<< orphan*/ ,TYPE_5__*,TYPE_6__*) ; 

__attribute__((used)) static int av1_frame_split_filter(AVBSFContext *ctx, AVPacket *out)
{
    AV1FSplitContext *s = ctx->priv_data;
    CodedBitstreamFragment *td = &s->temporal_unit;
    int i, ret;
    int split = !!s->buffer_pkt->data;

    if (!s->buffer_pkt->data) {
        int nb_frames = 0;

        ret = ff_bsf_get_packet_ref(ctx, s->buffer_pkt);
        if (ret < 0)
            return ret;

        ret = ff_cbs_read_packet(s->cbc, td, s->buffer_pkt);
        if (ret < 0) {
            av_log(ctx, AV_LOG_WARNING, "Failed to parse temporal unit.\n");
            goto passthrough;
        }

        for (i = 0; i < td->nb_units; i++) {
            CodedBitstreamUnit *unit = &td->units[i];

            if (unit->type == AV1_OBU_FRAME ||
                unit->type == AV1_OBU_FRAME_HEADER)
                nb_frames++;
            else if (unit->type == AV1_OBU_TILE_LIST) {
                av_log(ctx, AV_LOG_VERBOSE, "Large scale tiles are unsupported.\n");
                goto passthrough;
            }
        }
        if (nb_frames > 1) {
            s->cur_frame = 0;
            s->cur_frame_idx = s->last_frame_idx = 0;
            s->nb_frames = nb_frames;
            split = 1;
        }
    }

    if (split) {
        AV1RawFrameHeader *frame = NULL;
        int cur_frame_type = -1, size = 0;

        for (i = s->cur_frame_idx; i < td->nb_units; i++) {
            CodedBitstreamUnit *unit = &td->units[i];

            size += unit->data_size;
            if (unit->type == AV1_OBU_FRAME) {
                AV1RawOBU *obu = unit->content;

                if (frame) {
                    av_log(ctx, AV_LOG_WARNING, "Frame OBU found when Tile data for a "
                                                "previous frame was expected.\n");
                    goto passthrough;
                }

                frame = &obu->obu.frame.header;
                cur_frame_type = obu->header.obu_type;
                s->last_frame_idx = s->cur_frame_idx;
                s->cur_frame_idx  = i + 1;
                s->cur_frame++;

                // split here unless it's the last frame, in which case
                // include every trailing OBU
                if (s->cur_frame < s->nb_frames)
                    break;
            } else if (unit->type == AV1_OBU_FRAME_HEADER) {
                AV1RawOBU *obu = unit->content;

                if (frame) {
                    av_log(ctx, AV_LOG_WARNING, "Frame Header OBU found when Tile data for a "
                                                "previous frame was expected.\n");
                    goto passthrough;
                }

                frame = &obu->obu.frame_header;
                cur_frame_type = obu->header.obu_type;
                s->last_frame_idx = s->cur_frame_idx;
                s->cur_frame++;

                // split here if show_existing_frame unless it's the last
                // frame, in which case include every trailing OBU
                if (frame->show_existing_frame &&
                    s->cur_frame < s->nb_frames) {
                    s->cur_frame_idx = i + 1;
                    break;
                }
            } else if (unit->type == AV1_OBU_TILE_GROUP) {
                AV1RawOBU *obu = unit->content;
                AV1RawTileGroup *group = &obu->obu.tile_group;

                if (!frame || cur_frame_type != AV1_OBU_FRAME_HEADER) {
                    av_log(ctx, AV_LOG_WARNING, "Unexpected Tile Group OBU found before a "
                                                "Frame Header.\n");
                    goto passthrough;
                }

                if ((group->tg_end == (frame->tile_cols * frame->tile_rows) - 1) &&
                    // include every trailing OBU with the last frame
                    s->cur_frame < s->nb_frames) {
                    s->cur_frame_idx = i + 1;
                    break;
                }
            }
        }
        av_assert0(frame && s->cur_frame <= s->nb_frames);

        ret = av_packet_ref(out, s->buffer_pkt);
        if (ret < 0)
            goto fail;

        out->data = (uint8_t *)td->units[s->last_frame_idx].data;
        out->size = size;

        // skip the frame in the buffer packet if it's split successfully, so it's not present
        // if the packet is passed through in case of failure when splitting another frame.
        s->buffer_pkt->data += size;
        s->buffer_pkt->size -= size;

        if (!frame->show_existing_frame && !frame->show_frame)
            out->pts = AV_NOPTS_VALUE;

        if (s->cur_frame == s->nb_frames) {
            av_packet_unref(s->buffer_pkt);
            ff_cbs_fragment_reset(s->cbc, td);
        }

        return 0;
    }

passthrough:
    av_packet_move_ref(out, s->buffer_pkt);

    ret = 0;
fail:
    if (ret < 0) {
        av_packet_unref(out);
        av_packet_unref(s->buffer_pkt);
    }
    ff_cbs_fragment_reset(s->cbc, td);

    return ret;
}