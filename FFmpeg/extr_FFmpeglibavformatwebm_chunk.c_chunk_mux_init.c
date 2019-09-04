#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int chunk_duration; TYPE_3__* avf; int /*<<< orphan*/  oformat; } ;
typedef  TYPE_2__ WebMChunkContext ;
struct TYPE_10__ {int /*<<< orphan*/  nb_streams; int /*<<< orphan*/  streams; TYPE_2__* priv_data; TYPE_1__* oformat; int /*<<< orphan*/  metadata; int /*<<< orphan*/  max_delay; int /*<<< orphan*/  interrupt_callback; } ;
struct TYPE_8__ {int /*<<< orphan*/ * priv_class; } ;
typedef  TYPE_3__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVClass ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_opt_set_defaults (TYPE_2__*) ; 
 int /*<<< orphan*/  av_opt_set_int (TYPE_2__*,char*,int,int /*<<< orphan*/ ) ; 
 int avformat_alloc_output_context2 (TYPE_3__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chunk_mux_init(AVFormatContext *s)
{
    WebMChunkContext *wc = s->priv_data;
    AVFormatContext *oc;
    int ret;

    ret = avformat_alloc_output_context2(&wc->avf, wc->oformat, NULL, NULL);
    if (ret < 0)
        return ret;
    oc = wc->avf;

    oc->interrupt_callback = s->interrupt_callback;
    oc->max_delay          = s->max_delay;
    av_dict_copy(&oc->metadata, s->metadata, 0);

    *(const AVClass**)oc->priv_data = oc->oformat->priv_class;
    av_opt_set_defaults(oc->priv_data);
    av_opt_set_int(oc->priv_data, "dash", 1, 0);
    av_opt_set_int(oc->priv_data, "cluster_time_limit", wc->chunk_duration, 0);
    av_opt_set_int(oc->priv_data, "live", 1, 0);

    oc->streams = s->streams;
    oc->nb_streams = s->nb_streams;

    return 0;
}