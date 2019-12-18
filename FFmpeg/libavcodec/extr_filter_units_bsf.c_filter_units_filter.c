#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_2__* priv_data; } ;
struct TYPE_14__ {int nb_units; TYPE_1__* units; } ;
struct TYPE_13__ {scalar_t__ mode; int nb_types; scalar_t__* type_list; int /*<<< orphan*/  cbc; TYPE_3__ fragment; } ;
struct TYPE_12__ {scalar_t__ type; } ;
typedef  TYPE_2__ FilterUnitsContext ;
typedef  TYPE_3__ CodedBitstreamFragment ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_4__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ NOOP ; 
 scalar_t__ REMOVE ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int ff_bsf_get_packet_ref (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_cbs_delete_unit (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ff_cbs_fragment_reset (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int ff_cbs_read_packet (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ff_cbs_write_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int filter_units_filter(AVBSFContext *bsf, AVPacket *pkt)
{
    FilterUnitsContext      *ctx = bsf->priv_data;
    CodedBitstreamFragment *frag = &ctx->fragment;
    int err, i, j;

    err = ff_bsf_get_packet_ref(bsf, pkt);
    if (err < 0)
        return err;

    if (ctx->mode == NOOP)
        return 0;

    err = ff_cbs_read_packet(ctx->cbc, frag, pkt);
    if (err < 0) {
        av_log(bsf, AV_LOG_ERROR, "Failed to read packet.\n");
        goto fail;
    }

    for (i = frag->nb_units - 1; i >= 0; i--) {
        for (j = 0; j < ctx->nb_types; j++) {
            if (frag->units[i].type == ctx->type_list[j])
                break;
        }
        if (ctx->mode == REMOVE ? j <  ctx->nb_types
                                : j >= ctx->nb_types)
            ff_cbs_delete_unit(ctx->cbc, frag, i);
    }

    if (frag->nb_units == 0) {
        // Don't return packets with nothing in them.
        err = AVERROR(EAGAIN);
        goto fail;
    }

    err = ff_cbs_write_packet(ctx->cbc, pkt, frag);
    if (err < 0) {
        av_log(bsf, AV_LOG_ERROR, "Failed to write packet.\n");
        goto fail;
    }

fail:
    if (err < 0)
        av_packet_unref(pkt);
    ff_cbs_fragment_reset(ctx->cbc, frag);

    return err;
}