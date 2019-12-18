#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int format; TYPE_1__* dst; } ;
struct TYPE_11__ {int nb_samples; scalar_t__* extended_data; } ;
struct TYPE_10__ {int nb_channels; int /*<<< orphan*/ * chstats; } ;
struct TYPE_9__ {int /*<<< orphan*/ * outputs; TYPE_2__* priv; } ;
typedef  TYPE_2__ DRMeterContext ;
typedef  int /*<<< orphan*/  ChannelStats ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
#define  AV_SAMPLE_FMT_FLT 129 
#define  AV_SAMPLE_FMT_FLTP 128 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  update_stat (TYPE_2__*,int /*<<< orphan*/ *,float const) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *buf)
{
    DRMeterContext *s = inlink->dst->priv;
    const int channels = s->nb_channels;
    int i, c;

    switch (inlink->format) {
    case AV_SAMPLE_FMT_FLTP:
        for (c = 0; c < channels; c++) {
            ChannelStats *p = &s->chstats[c];
            const float *src = (const float *)buf->extended_data[c];

            for (i = 0; i < buf->nb_samples; i++, src++)
                update_stat(s, p, *src);
        }
        break;
    case AV_SAMPLE_FMT_FLT: {
        const float *src = (const float *)buf->extended_data[0];

        for (i = 0; i < buf->nb_samples; i++) {
            for (c = 0; c < channels; c++, src++)
                update_stat(s, &s->chstats[c], *src);
        }}
        break;
    }

    return ff_filter_frame(inlink->dst->outputs[0], buf);
}