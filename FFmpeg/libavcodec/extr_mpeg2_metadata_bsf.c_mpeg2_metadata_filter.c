#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  cbc; int /*<<< orphan*/  fragment; } ;
typedef  TYPE_1__ MPEG2MetadataContext ;
typedef  int /*<<< orphan*/  CodedBitstreamFragment ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int ff_bsf_get_packet_ref (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_cbs_fragment_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ff_cbs_read_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_cbs_write_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mpeg2_metadata_update_fragment (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mpeg2_metadata_filter(AVBSFContext *bsf, AVPacket *pkt)
{
    MPEG2MetadataContext *ctx = bsf->priv_data;
    CodedBitstreamFragment *frag = &ctx->fragment;
    int err;

    err = ff_bsf_get_packet_ref(bsf, pkt);
    if (err < 0)
        return err;

    err = ff_cbs_read_packet(ctx->cbc, frag, pkt);
    if (err < 0) {
        av_log(bsf, AV_LOG_ERROR, "Failed to read packet.\n");
        goto fail;
    }

    err = mpeg2_metadata_update_fragment(bsf, frag);
    if (err < 0) {
        av_log(bsf, AV_LOG_ERROR, "Failed to update frame fragment.\n");
        goto fail;
    }

    err = ff_cbs_write_packet(ctx->cbc, pkt, frag);
    if (err < 0) {
        av_log(bsf, AV_LOG_ERROR, "Failed to write packet.\n");
        goto fail;
    }

    err = 0;
fail:
    ff_cbs_fragment_reset(ctx->cbc, frag);

    if (err < 0)
        av_packet_unref(pkt);

    return err;
}