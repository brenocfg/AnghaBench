#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ data; } ;
struct TYPE_9__ {scalar_t__ extra_hw_frames; } ;
struct TYPE_8__ {TYPE_6__* hw_frames_ctx; } ;
struct TYPE_7__ {int initial_pool_size; } ;
typedef  TYPE_1__ AVHWFramesContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (TYPE_6__*) ; 

int ff_filter_init_hw_frames(AVFilterContext *avctx, AVFilterLink *link,
                             int default_pool_size)
{
    AVHWFramesContext *frames;

    // Must already be set by caller.
    av_assert0(link->hw_frames_ctx);

    frames = (AVHWFramesContext*)link->hw_frames_ctx->data;

    if (frames->initial_pool_size == 0) {
        // Dynamic allocation is necessarily supported.
    } else if (avctx->extra_hw_frames >= 0) {
        frames->initial_pool_size += avctx->extra_hw_frames;
    } else {
        frames->initial_pool_size = default_pool_size;
    }

    return 0;
}