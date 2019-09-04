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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int use_subsamples; int /*<<< orphan*/  aes_ctr; } ;
typedef  TYPE_1__ MOVMuxCencContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_aes_ctr_alloc () ; 
 int av_aes_ctr_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_aes_ctr_set_random_iv (int /*<<< orphan*/ ) ; 

int ff_mov_cenc_init(MOVMuxCencContext* ctx, uint8_t* encryption_key,
                     int use_subsamples, int bitexact)
{
    int ret;

    ctx->aes_ctr = av_aes_ctr_alloc();
    if (!ctx->aes_ctr) {
        return AVERROR(ENOMEM);
    }

    ret = av_aes_ctr_init(ctx->aes_ctr, encryption_key);
    if (ret != 0) {
        return ret;
    }

    if (!bitexact) {
        av_aes_ctr_set_random_iv(ctx->aes_ctr);
    }

    ctx->use_subsamples = use_subsamples;

    return 0;
}