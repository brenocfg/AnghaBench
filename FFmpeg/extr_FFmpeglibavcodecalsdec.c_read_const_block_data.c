#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ block_length; int* const_block; scalar_t__* raw_samples; void* js_blocks; } ;
struct TYPE_8__ {scalar_t__ floating; } ;
struct TYPE_9__ {int /*<<< orphan*/  gb; TYPE_1__* avctx; TYPE_2__ sconf; } ;
struct TYPE_7__ {int bits_per_raw_sample; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AVCodecContext ;
typedef  TYPE_2__ ALSSpecificConfig ;
typedef  TYPE_3__ ALSDecContext ;
typedef  TYPE_4__ ALSBlockData ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 void* get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_sbits_long (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_const_block_data(ALSDecContext *ctx, ALSBlockData *bd)
{
    ALSSpecificConfig *sconf = &ctx->sconf;
    AVCodecContext *avctx    = ctx->avctx;
    GetBitContext *gb        = &ctx->gb;

    if (bd->block_length <= 0)
        return AVERROR_INVALIDDATA;

    *bd->raw_samples = 0;
    *bd->const_block = get_bits1(gb);    // 1 = constant value, 0 = zero block (silence)
    bd->js_blocks    = get_bits1(gb);

    // skip 5 reserved bits
    skip_bits(gb, 5);

    if (*bd->const_block) {
        unsigned int const_val_bits = sconf->floating ? 24 : avctx->bits_per_raw_sample;
        *bd->raw_samples = get_sbits_long(gb, const_val_bits);
    }

    // ensure constant block decoding by reusing this field
    *bd->const_block = 1;

    return 0;
}