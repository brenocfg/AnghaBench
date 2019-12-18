#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int auxiliary_info_entries; int auxiliary_info_sizes_alloc_size; int /*<<< orphan*/  subsample_count; scalar_t__ auxiliary_info_subsample_start; scalar_t__ auxiliary_info; scalar_t__ auxiliary_info_size; scalar_t__* auxiliary_info_sizes; int /*<<< orphan*/  use_subsamples; int /*<<< orphan*/  aes_ctr; } ;
typedef  TYPE_1__ MOVMuxCencContext ;

/* Variables and functions */
 scalar_t__ AES_CTR_IV_SIZE ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WB16 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_aes_ctr_increment_iv (int /*<<< orphan*/ ) ; 
 scalar_t__ av_reallocp (scalar_t__**,size_t) ; 

__attribute__((used)) static int mov_cenc_end_packet(MOVMuxCencContext* ctx)
{
    size_t new_alloc_size;

    av_aes_ctr_increment_iv(ctx->aes_ctr);

    if (!ctx->use_subsamples) {
        ctx->auxiliary_info_entries++;
        return 0;
    }

    /* add the auxiliary info entry size*/
    if (ctx->auxiliary_info_entries >= ctx->auxiliary_info_sizes_alloc_size) {
        new_alloc_size = ctx->auxiliary_info_entries * 2 + 1;
        if (av_reallocp(&ctx->auxiliary_info_sizes, new_alloc_size)) {
            return AVERROR(ENOMEM);
        }

        ctx->auxiliary_info_sizes_alloc_size = new_alloc_size;
    }
    ctx->auxiliary_info_sizes[ctx->auxiliary_info_entries] =
        AES_CTR_IV_SIZE + ctx->auxiliary_info_size - ctx->auxiliary_info_subsample_start;
    ctx->auxiliary_info_entries++;

    /* update the subsample count*/
    AV_WB16(ctx->auxiliary_info + ctx->auxiliary_info_subsample_start, ctx->subsample_count);

    return 0;
}