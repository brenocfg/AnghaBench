#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cbc; int /*<<< orphan*/  pkt; int /*<<< orphan*/  in; int /*<<< orphan*/ * frag; } ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ AVBSFContext ;
typedef  TYPE_2__ AV1FMergeContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_packet_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_cbs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_cbs_fragment_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void av1_frame_merge_close(AVBSFContext *bsf)
{
    AV1FMergeContext *ctx = bsf->priv_data;

    ff_cbs_fragment_free(ctx->cbc, &ctx->frag[0]);
    ff_cbs_fragment_free(ctx->cbc, &ctx->frag[1]);
    av_packet_free(&ctx->in);
    av_packet_free(&ctx->pkt);
    ff_cbs_close(&ctx->cbc);
}