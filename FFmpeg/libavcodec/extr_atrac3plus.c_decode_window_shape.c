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
struct TYPE_5__ {int /*<<< orphan*/  num_subbands; TYPE_1__* channels; } ;
struct TYPE_4__ {int /*<<< orphan*/  wnd_shape; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ Atrac3pChanUnitCtx ;

/* Variables and functions */
 int /*<<< orphan*/  get_subband_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decode_window_shape(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                                int num_channels)
{
    int ch_num;

    for (ch_num = 0; ch_num < num_channels; ch_num++)
        get_subband_flags(gb, ctx->channels[ch_num].wnd_shape,
                          ctx->num_subbands);
}