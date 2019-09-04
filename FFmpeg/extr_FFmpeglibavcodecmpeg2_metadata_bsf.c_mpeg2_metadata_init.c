#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ extradata; } ;
struct TYPE_9__ {int /*<<< orphan*/  par_out; TYPE_5__* par_in; TYPE_1__* priv_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  cbc; int /*<<< orphan*/  fragment; } ;
typedef  TYPE_1__ MPEG2MetadataContext ;
typedef  int /*<<< orphan*/  CodedBitstreamFragment ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_MPEG2VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_cbs_fragment_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ff_cbs_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int ff_cbs_read_extradata (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int ff_cbs_write_extradata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mpeg2_metadata_update_fragment (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpeg2_metadata_init(AVBSFContext *bsf)
{
    MPEG2MetadataContext *ctx = bsf->priv_data;
    CodedBitstreamFragment *frag = &ctx->fragment;
    int err;

    err = ff_cbs_init(&ctx->cbc, AV_CODEC_ID_MPEG2VIDEO, bsf);
    if (err < 0)
        return err;

    if (bsf->par_in->extradata) {
        err = ff_cbs_read_extradata(ctx->cbc, frag, bsf->par_in);
        if (err < 0) {
            av_log(bsf, AV_LOG_ERROR, "Failed to read extradata.\n");
            goto fail;
        }

        err = mpeg2_metadata_update_fragment(bsf, frag);
        if (err < 0) {
            av_log(bsf, AV_LOG_ERROR, "Failed to update metadata fragment.\n");
            goto fail;
        }

        err = ff_cbs_write_extradata(ctx->cbc, bsf->par_out, frag);
        if (err < 0) {
            av_log(bsf, AV_LOG_ERROR, "Failed to write extradata.\n");
            goto fail;
        }
    }

    err = 0;
fail:
    ff_cbs_fragment_reset(ctx->cbc, frag);
    return err;
}