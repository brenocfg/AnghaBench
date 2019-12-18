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
struct TYPE_5__ {int /*<<< orphan*/  pkt; int /*<<< orphan*/  in; int /*<<< orphan*/ * frag; int /*<<< orphan*/  cbc; } ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ AVBSFContext ;
typedef  TYPE_2__ AV1FMergeContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_cbs_fragment_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void av1_frame_merge_flush(AVBSFContext *bsf)
{
    AV1FMergeContext *ctx = bsf->priv_data;

    ff_cbs_fragment_reset(ctx->cbc, &ctx->frag[0]);
    ff_cbs_fragment_reset(ctx->cbc, &ctx->frag[1]);
    av_packet_unref(ctx->in);
    av_packet_unref(ctx->pkt);
}