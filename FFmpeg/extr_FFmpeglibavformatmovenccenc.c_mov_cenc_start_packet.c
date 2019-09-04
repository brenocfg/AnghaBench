#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {scalar_t__ subsample_count; int /*<<< orphan*/  auxiliary_info_size; int /*<<< orphan*/  auxiliary_info_subsample_start; int /*<<< orphan*/  use_subsamples; int /*<<< orphan*/  aes_ctr; } ;
typedef  TYPE_1__ MOVMuxCencContext ;

/* Variables and functions */
 int AES_CTR_IV_SIZE ; 
 int auxiliary_info_write (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * av_aes_ctr_get_iv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_cenc_start_packet(MOVMuxCencContext* ctx)
{
    int ret;

    /* write the iv */
    ret = auxiliary_info_write(ctx, av_aes_ctr_get_iv(ctx->aes_ctr), AES_CTR_IV_SIZE);
    if (ret) {
        return ret;
    }

    if (!ctx->use_subsamples) {
        return 0;
    }

    /* write a zero subsample count */
    ctx->auxiliary_info_subsample_start = ctx->auxiliary_info_size;
    ctx->subsample_count = 0;
    ret = auxiliary_info_write(ctx, (uint8_t*)&ctx->subsample_count, sizeof(ctx->subsample_count));
    if (ret) {
        return ret;
    }

    return 0;
}