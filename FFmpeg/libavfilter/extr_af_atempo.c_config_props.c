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
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_5__ {int /*<<< orphan*/ * priv; } ;
struct TYPE_4__ {int format; int /*<<< orphan*/  channels; scalar_t__ sample_rate; TYPE_2__* dst; } ;
typedef  TYPE_1__ AVFilterLink ;
typedef  TYPE_2__ AVFilterContext ;
typedef  int /*<<< orphan*/  ATempoContext ;

/* Variables and functions */
 int yae_reset (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_props(AVFilterLink *inlink)
{
    AVFilterContext  *ctx = inlink->dst;
    ATempoContext *atempo = ctx->priv;

    enum AVSampleFormat format = inlink->format;
    int sample_rate = (int)inlink->sample_rate;

    return yae_reset(atempo, format, sample_rate, inlink->channels);
}