#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_7__ {TYPE_2__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  nb_samples; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channel_layout; } ;
struct TYPE_5__ {TYPE_4__* src; } ;
typedef  TYPE_1__ AVFilterLink ;
typedef  TYPE_2__ ANullContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  av_get_channel_layout_string (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_props(AVFilterLink *outlink)
{
    ANullContext *null = outlink->src->priv;
    char buf[128];

    av_get_channel_layout_string(buf, sizeof(buf), 0, null->channel_layout);
    av_log(outlink->src, AV_LOG_VERBOSE,
           "sample_rate:%d channel_layout:'%s' nb_samples:%d\n",
           null->sample_rate, buf, null->nb_samples);

    return 0;
}