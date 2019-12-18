#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  par_out; TYPE_12__* par_in; TYPE_2__* priv_data; } ;
struct TYPE_19__ {int nb_units; TYPE_1__* units; } ;
struct TYPE_18__ {scalar_t__ level; int /*<<< orphan*/  cbc; TYPE_3__ access_unit; } ;
struct TYPE_17__ {scalar_t__ type; int /*<<< orphan*/  content; } ;
struct TYPE_16__ {scalar_t__ extradata; } ;
typedef  TYPE_2__ H265MetadataContext ;
typedef  TYPE_3__ CodedBitstreamFragment ;
typedef  TYPE_4__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_HEVC ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ HEVC_NAL_SPS ; 
 scalar_t__ HEVC_NAL_VPS ; 
 scalar_t__ LEVEL_AUTO ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_cbs_fragment_reset (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int ff_cbs_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int ff_cbs_read_extradata (int /*<<< orphan*/ ,TYPE_3__*,TYPE_12__*) ; 
 int ff_cbs_write_extradata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  h265_metadata_guess_level (TYPE_4__*,TYPE_3__*) ; 
 int h265_metadata_update_sps (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int h265_metadata_update_vps (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int h265_metadata_init(AVBSFContext *bsf)
{
    H265MetadataContext *ctx = bsf->priv_data;
    CodedBitstreamFragment *au = &ctx->access_unit;
    int err, i;

    err = ff_cbs_init(&ctx->cbc, AV_CODEC_ID_HEVC, bsf);
    if (err < 0)
        return err;

    if (bsf->par_in->extradata) {
        err = ff_cbs_read_extradata(ctx->cbc, au, bsf->par_in);
        if (err < 0) {
            av_log(bsf, AV_LOG_ERROR, "Failed to read extradata.\n");
            goto fail;
        }

        if (ctx->level == LEVEL_AUTO)
            h265_metadata_guess_level(bsf, au);

        for (i = 0; i < au->nb_units; i++) {
            if (au->units[i].type == HEVC_NAL_VPS) {
                err = h265_metadata_update_vps(bsf, au->units[i].content);
                if (err < 0)
                    goto fail;
            }
            if (au->units[i].type == HEVC_NAL_SPS) {
                err = h265_metadata_update_sps(bsf, au->units[i].content);
                if (err < 0)
                    goto fail;
            }
        }

        err = ff_cbs_write_extradata(ctx->cbc, bsf->par_out, au);
        if (err < 0) {
            av_log(bsf, AV_LOG_ERROR, "Failed to write extradata.\n");
            goto fail;
        }
    }

    err = 0;
fail:
    ff_cbs_fragment_reset(ctx->cbc, au);
    return err;
}