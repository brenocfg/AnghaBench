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
struct TYPE_12__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_11__ {int n_streams; int prev_set_id; int prev_stream_id; int prev_timestamp; void* dynamic_protocol_context; int /*<<< orphan*/ * parse_packet; TYPE_1__** streams; TYPE_4__* ic; } ;
struct TYPE_10__ {int /*<<< orphan*/ * parse_packet; } ;
struct TYPE_9__ {scalar_t__ id; } ;
typedef  TYPE_2__ RTPDynamicProtocolHandler ;
typedef  TYPE_3__ RDTDemuxContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 TYPE_3__* av_mallocz (int) ; 

RDTDemuxContext *
ff_rdt_parse_open(AVFormatContext *ic, int first_stream_of_set_idx,
                  void *priv_data, const RTPDynamicProtocolHandler *handler)
{
    RDTDemuxContext *s = av_mallocz(sizeof(RDTDemuxContext));
    if (!s)
        return NULL;

    s->ic = ic;
    s->streams = &ic->streams[first_stream_of_set_idx];
    do {
        s->n_streams++;
    } while (first_stream_of_set_idx + s->n_streams < ic->nb_streams &&
             s->streams[s->n_streams]->id == s->streams[0]->id);
    s->prev_set_id    = -1;
    s->prev_stream_id = -1;
    s->prev_timestamp = -1;
    s->parse_packet = handler ? handler->parse_packet : NULL;
    s->dynamic_protocol_context = priv_data;

    return s;
}