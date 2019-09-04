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
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  gb; int /*<<< orphan*/  avctx; } ;
struct TYPE_5__ {int max_bits; size_t num; size_t max_num; int* bits; int* lens; int /*<<< orphan*/  val_bits; int /*<<< orphan*/ * nums; } ;
typedef  TYPE_1__ TM2Huff ;
typedef  TYPE_2__ TM2Context ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int FFMAX (int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tm2_read_tree(TM2Context *ctx, uint32_t prefix, int length, TM2Huff *huff)
{
    int ret, ret2;
    if (length > huff->max_bits) {
        av_log(ctx->avctx, AV_LOG_ERROR, "Tree exceeded its given depth (%i)\n",
               huff->max_bits);
        return AVERROR_INVALIDDATA;
    }

    if (!get_bits1(&ctx->gb)) { /* literal */
        if (length == 0) {
            length = 1;
        }
        if (huff->num >= huff->max_num) {
            av_log(ctx->avctx, AV_LOG_DEBUG, "Too many literals\n");
            return AVERROR_INVALIDDATA;
        }
        huff->nums[huff->num] = get_bits_long(&ctx->gb, huff->val_bits);
        huff->bits[huff->num] = prefix;
        huff->lens[huff->num] = length;
        huff->num++;
        return length;
    } else { /* non-terminal node */
        if ((ret2 = tm2_read_tree(ctx, prefix << 1, length + 1, huff)) < 0)
            return ret2;
        if ((ret = tm2_read_tree(ctx, (prefix << 1) | 1, length + 1, huff)) < 0)
            return ret;
    }
    return FFMAX(ret, ret2);
}