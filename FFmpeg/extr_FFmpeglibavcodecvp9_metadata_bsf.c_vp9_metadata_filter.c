#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ color_space; scalar_t__ color_range; } ;
typedef  TYPE_2__ VP9RawFrameHeader ;
struct TYPE_15__ {TYPE_2__ header; } ;
typedef  TYPE_3__ VP9RawFrame ;
struct TYPE_17__ {int nb_units; TYPE_1__* units; } ;
struct TYPE_16__ {scalar_t__ color_space; scalar_t__ color_range; int color_range_rgb_warned; int /*<<< orphan*/  cbc; TYPE_5__ fragment; } ;
typedef  TYPE_4__ VP9MetadataContext ;
struct TYPE_18__ {TYPE_4__* priv_data; } ;
struct TYPE_13__ {TYPE_3__* content; } ;
typedef  TYPE_5__ CodedBitstreamFragment ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_6__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ VP9_CS_RGB ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int av_packet_copy_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_packet_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int ff_bsf_get_packet (TYPE_6__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_cbs_fragment_reset (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int ff_cbs_read_packet (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int ff_cbs_write_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static int vp9_metadata_filter(AVBSFContext *bsf, AVPacket *out)
{
    VP9MetadataContext *ctx = bsf->priv_data;
    AVPacket *in = NULL;
    CodedBitstreamFragment *frag = &ctx->fragment;
    int err, i;

    err = ff_bsf_get_packet(bsf, &in);
    if (err < 0)
        return err;

    err = ff_cbs_read_packet(ctx->cbc, frag, in);
    if (err < 0) {
        av_log(bsf, AV_LOG_ERROR, "Failed to read packet.\n");
        goto fail;
    }

    for (i = 0; i < frag->nb_units; i++) {
        VP9RawFrame *frame = frag->units[i].content;
        VP9RawFrameHeader *header = &frame->header;

        if (ctx->color_space >= 0) {
            header->color_space = ctx->color_space;
        }
        if (ctx->color_range >= 0) {
            if (ctx->color_range == 0 &&
                header->color_space == VP9_CS_RGB &&
                !ctx->color_range_rgb_warned) {
                av_log(bsf, AV_LOG_WARNING, "Warning: color_range cannot "
                       "be set to limited in RGB streams.\n");
                ctx->color_range_rgb_warned = 1;
            } else {
                header->color_range = ctx->color_range;
            }
        }
    }

    err = ff_cbs_write_packet(ctx->cbc, out, frag);
    if (err < 0) {
        av_log(bsf, AV_LOG_ERROR, "Failed to write packet.\n");
        goto fail;
    }

    err = av_packet_copy_props(out, in);
    if (err < 0)
        goto fail;

    err = 0;
fail:
    ff_cbs_fragment_reset(ctx->cbc, frag);

    if (err < 0)
        av_packet_unref(out);
    av_packet_free(&in);

    return err;
}