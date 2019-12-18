#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct speex_params {int packet_size; scalar_t__ final_packet_duration; } ;
struct ogg_stream {int flags; scalar_t__ lastpts; scalar_t__ granule; scalar_t__ lastdts; scalar_t__ segp; scalar_t__ nsegs; scalar_t__ pduration; struct speex_params* private; } ;
struct ogg {struct ogg_stream* streams; } ;
struct TYPE_3__ {struct ogg* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int OGG_FLAG_EOS ; 
 int ogg_page_packets (struct ogg_stream*) ; 

__attribute__((used)) static int speex_packet(AVFormatContext *s, int idx)
{
    struct ogg *ogg = s->priv_data;
    struct ogg_stream *os = ogg->streams + idx;
    struct speex_params *spxp = os->private;
    int packet_size = spxp->packet_size;

    if (os->flags & OGG_FLAG_EOS && os->lastpts != AV_NOPTS_VALUE &&
        os->granule > 0) {
        /* first packet of final page. we have to calculate the final packet
           duration here because it is the only place we know the next-to-last
           granule position. */
        spxp->final_packet_duration = os->granule - os->lastpts -
                                      packet_size * (ogg_page_packets(os) - 1);
    }

    if (!os->lastpts && os->granule > 0)
        /* first packet */
        os->lastpts = os->lastdts = os->granule - packet_size *
                                    ogg_page_packets(os);
    if (os->flags & OGG_FLAG_EOS && os->segp == os->nsegs &&
        spxp->final_packet_duration)
        /* final packet */
        os->pduration = spxp->final_packet_duration;
    else
        os->pduration = packet_size;

    return 0;
}