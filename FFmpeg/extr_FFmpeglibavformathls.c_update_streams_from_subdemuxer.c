#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct playlist {int n_main_streams; int /*<<< orphan*/  main_streams; int /*<<< orphan*/  index; TYPE_1__* ctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int nb_streams; TYPE_2__** streams; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  add_stream_to_programs (int /*<<< orphan*/ *,struct playlist*,TYPE_2__*) ; 
 TYPE_2__* avformat_new_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dynarray_add (int /*<<< orphan*/ *,int*,TYPE_2__*) ; 
 int set_stream_info_from_input_stream (TYPE_2__*,struct playlist*,TYPE_2__*) ; 

__attribute__((used)) static int update_streams_from_subdemuxer(AVFormatContext *s, struct playlist *pls)
{
    int err;

    while (pls->n_main_streams < pls->ctx->nb_streams) {
        int ist_idx = pls->n_main_streams;
        AVStream *st = avformat_new_stream(s, NULL);
        AVStream *ist = pls->ctx->streams[ist_idx];

        if (!st)
            return AVERROR(ENOMEM);

        st->id = pls->index;
        dynarray_add(&pls->main_streams, &pls->n_main_streams, st);

        add_stream_to_programs(s, pls, st);

        err = set_stream_info_from_input_stream(st, pls, ist);
        if (err < 0)
            return err;
    }

    return 0;
}