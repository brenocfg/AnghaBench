#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cbc; void* pkt; void* in; } ;
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ AVBSFContext ;
typedef  TYPE_2__ AV1FMergeContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_CODEC_ID_AV1 ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* av_packet_alloc () ; 
 int ff_cbs_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int av1_frame_merge_init(AVBSFContext *bsf)
{
    AV1FMergeContext *ctx = bsf->priv_data;

    ctx->in  = av_packet_alloc();
    ctx->pkt = av_packet_alloc();
    if (!ctx->in || !ctx->pkt)
        return AVERROR(ENOMEM);

    return ff_cbs_init(&ctx->cbc, AV_CODEC_ID_AV1, bsf);
}