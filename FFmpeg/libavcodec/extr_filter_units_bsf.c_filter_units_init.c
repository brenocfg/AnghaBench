#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ extradata; int /*<<< orphan*/  codec_id; } ;
struct TYPE_13__ {scalar_t__ nb_decompose_unit_types; int /*<<< orphan*/  decompose_unit_types; } ;
struct TYPE_12__ {int /*<<< orphan*/  par_out; TYPE_6__* par_in; TYPE_1__* priv_data; } ;
struct TYPE_11__ {TYPE_4__* cbc; int /*<<< orphan*/  fragment; int /*<<< orphan*/  type_list; int /*<<< orphan*/  nb_types; scalar_t__ remove_types; int /*<<< orphan*/  mode; scalar_t__ pass_types; } ;
typedef  TYPE_1__ FilterUnitsContext ;
typedef  int /*<<< orphan*/  CodedBitstreamFragment ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PASS ; 
 int /*<<< orphan*/  REMOVE ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_cbs_fragment_reset (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int ff_cbs_init (TYPE_4__**,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ff_cbs_read_extradata (TYPE_4__*,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int ff_cbs_write_extradata (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int filter_units_make_type_list (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int filter_units_init(AVBSFContext *bsf)
{
    FilterUnitsContext *ctx = bsf->priv_data;
    int err;

    if (ctx->pass_types && ctx->remove_types) {
        av_log(bsf, AV_LOG_ERROR, "Exactly one of pass_types or "
               "remove_types is required.\n");
        return AVERROR(EINVAL);
    }

    if (ctx->pass_types) {
        ctx->mode = PASS;
        err = filter_units_make_type_list(ctx->pass_types,
                                          &ctx->type_list, &ctx->nb_types);
        if (err < 0) {
            av_log(bsf, AV_LOG_ERROR, "Failed to parse pass_types.\n");
            return err;
        }
    } else if (ctx->remove_types) {
        ctx->mode = REMOVE;
        err = filter_units_make_type_list(ctx->remove_types,
                                          &ctx->type_list, &ctx->nb_types);
        if (err < 0) {
            av_log(bsf, AV_LOG_ERROR, "Failed to parse remove_types.\n");
            return err;
        }
    } else {
        return 0;
    }

    err = ff_cbs_init(&ctx->cbc, bsf->par_in->codec_id, bsf);
    if (err < 0)
        return err;

    // Don't actually decompose anything, we only want the unit data.
    ctx->cbc->decompose_unit_types    = ctx->type_list;
    ctx->cbc->nb_decompose_unit_types = 0;

    if (bsf->par_in->extradata) {
        CodedBitstreamFragment *frag = &ctx->fragment;

        err = ff_cbs_read_extradata(ctx->cbc, frag, bsf->par_in);
        if (err < 0) {
            av_log(bsf, AV_LOG_ERROR, "Failed to read extradata.\n");
        } else {
            err = ff_cbs_write_extradata(ctx->cbc, bsf->par_out, frag);
            if (err < 0)
                av_log(bsf, AV_LOG_ERROR, "Failed to write extradata.\n");
        }

        ff_cbs_fragment_reset(ctx->cbc, frag);
    }

    return err;
}