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
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ NOOP ; 
 scalar_t__ REMOVE ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int av_packet_copy_props (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_packet_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_packet_move_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_bsf_get_packet (TYPE_4__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_cbs_delete_unit (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ff_cbs_fragment_reset (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int ff_cbs_read_packet (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int ff_cbs_write_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int filter_units_filter(AVBSFContext *bsf, AVPacket *out)
{
    FilterUnitsContext      *ctx = bsf->priv_data;
    CodedBitstreamFragment *frag = &ctx->fragment;
    AVPacket *in = NULL;
    int err, i, j;

    while (1) {
        err = ff_bsf_get_packet(bsf, &in);
        if (err < 0)
            return err;

        if (ctx->mode == NOOP) {
            av_packet_move_ref(out, in);
            av_packet_free(&in);
            return 0;
        }

        err = ff_cbs_read_packet(ctx->cbc, frag, in);
        if (err < 0) {
            av_log(bsf, AV_LOG_ERROR, "Failed to read packet.\n");
            goto fail;
        }

        for (i = 0; i < frag->nb_units; i++) {
            for (j = 0; j < ctx->nb_types; j++) {
                if (frag->units[i].type == ctx->type_list[j])
                    break;
            }
            if (ctx->mode == REMOVE ? j <  ctx->nb_types
                                    : j >= ctx->nb_types) {
                ff_cbs_delete_unit(ctx->cbc, frag, i);
                --i;
            }
        }

        if (frag->nb_units > 0)
            break;

        // Don't return packets with nothing in them.
        av_packet_free(&in);
        ff_cbs_fragment_reset(ctx->cbc, frag);
    }

    err = ff_cbs_write_packet(ctx->cbc, out, frag);
    if (err < 0) {
        av_log(bsf, AV_LOG_ERROR, "Failed to write packet.\n");
        goto fail;
    }

    err = av_packet_copy_props(out, in);
    if (err < 0)
        goto fail;

fail:
    ff_cbs_fragment_reset(ctx->cbc, frag);
    av_packet_free(&in);

    return err;
}