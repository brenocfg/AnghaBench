#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_8__ {int nb_inputs; TYPE_2__** inputs; } ;
struct TYPE_7__ {int channel_layout; } ;
struct TYPE_6__ {int out_channel; int input; int in_channel; } ;
typedef  TYPE_1__ ChannelMap ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */

__attribute__((used)) static void guess_map_matching(AVFilterContext *ctx, ChannelMap *ch,
                               uint64_t *inputs)
{
    int i;

    for (i = 0; i < ctx->nb_inputs; i++) {
        AVFilterLink *link = ctx->inputs[i];

        if (ch->out_channel & link->channel_layout &&
            !(ch->out_channel & inputs[i])) {
            ch->input      = i;
            ch->in_channel = ch->out_channel;
            inputs[i]     |= ch->out_channel;
            return;
        }
    }
}