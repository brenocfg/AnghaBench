#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int type; int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  time_base; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  hw_frames_ctx; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_1__* src; } ;
struct TYPE_6__ {int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  time_base; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  hw_frames_ctx; int /*<<< orphan*/  pixel_aspect; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ BufferSourceContext ;
typedef  TYPE_3__ AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_buffer_ref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_props(AVFilterLink *link)
{
    BufferSourceContext *c = link->src->priv;

    switch (link->type) {
    case AVMEDIA_TYPE_VIDEO:
        link->w = c->w;
        link->h = c->h;
        link->sample_aspect_ratio = c->pixel_aspect;

        if (c->hw_frames_ctx) {
            link->hw_frames_ctx = av_buffer_ref(c->hw_frames_ctx);
            if (!link->hw_frames_ctx)
                return AVERROR(ENOMEM);
        }
        break;
    case AVMEDIA_TYPE_AUDIO:
        if (!c->channel_layout)
            c->channel_layout = link->channel_layout;
        break;
    default:
        return AVERROR(EINVAL);
    }

    link->time_base = c->time_base;
    link->frame_rate = c->frame_rate;
    return 0;
}