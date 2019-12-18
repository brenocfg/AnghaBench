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
struct TYPE_5__ {int stereo_in; TYPE_1__* ch; scalar_t__ hybrid_bitrate; } ;
typedef  TYPE_2__ WavpackFrameContext ;
struct TYPE_4__ {int bitrate_acc; int bitrate_delta; void* error_limit; int /*<<< orphan*/  slow_level; } ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int LEVEL_DECAY (int /*<<< orphan*/ ) ; 
 int UINT_MAX ; 
 void* wp_exp2 (int) ; 

__attribute__((used)) static int update_error_limit(WavpackFrameContext *ctx)
{
    int i, br[2], sl[2];

    for (i = 0; i <= ctx->stereo_in; i++) {
        if (ctx->ch[i].bitrate_acc > UINT_MAX - ctx->ch[i].bitrate_delta)
            return AVERROR_INVALIDDATA;
        ctx->ch[i].bitrate_acc += ctx->ch[i].bitrate_delta;
        br[i]                   = ctx->ch[i].bitrate_acc >> 16;
        sl[i]                   = LEVEL_DECAY(ctx->ch[i].slow_level);
    }
    if (ctx->stereo_in && ctx->hybrid_bitrate) {
        int balance = (sl[1] - sl[0] + br[1] + 1) >> 1;
        if (balance > br[0]) {
            br[1] = br[0] * 2;
            br[0] = 0;
        } else if (-balance > br[0]) {
            br[0]  *= 2;
            br[1]   = 0;
        } else {
            br[1] = br[0] + balance;
            br[0] = br[0] - balance;
        }
    }
    for (i = 0; i <= ctx->stereo_in; i++) {
        if (ctx->hybrid_bitrate) {
            if (sl[i] - br[i] > -0x100)
                ctx->ch[i].error_limit = wp_exp2(sl[i] - br[i] + 0x100);
            else
                ctx->ch[i].error_limit = 0;
        } else {
            ctx->ch[i].error_limit = wp_exp2(br[i]);
        }
    }

    return 0;
}