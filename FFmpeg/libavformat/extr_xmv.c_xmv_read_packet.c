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
struct TYPE_8__ {scalar_t__ current_frame; scalar_t__ frame_count; } ;
struct TYPE_9__ {scalar_t__ current_stream; scalar_t__ stream_count; TYPE_1__ video; } ;
typedef  TYPE_2__ XMVDemuxContext ;
struct TYPE_10__ {TYPE_2__* priv_data; } ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int xmv_fetch_audio_packet (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int xmv_fetch_new_packet (TYPE_3__*) ; 
 int xmv_fetch_video_packet (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xmv_read_packet(AVFormatContext *s,
                           AVPacket *pkt)
{
    XMVDemuxContext *xmv = s->priv_data;
    int result;

    if (xmv->video.current_frame == xmv->video.frame_count) {
        /* No frames left in this packet, so we fetch a new one */

        result = xmv_fetch_new_packet(s);
        if (result)
            return result;
    }

    if (xmv->current_stream == 0) {
        /* Fetch a video frame */

        result = xmv_fetch_video_packet(s, pkt);
    } else {
        /* Fetch an audio frame */

        result = xmv_fetch_audio_packet(s, pkt, xmv->current_stream - 1);
    }
    if (result) {
        xmv->current_stream = 0;
        xmv->video.current_frame = xmv->video.frame_count;
        return result;
    }


    /* Increase our counters */
    if (++xmv->current_stream >= xmv->stream_count) {
        xmv->current_stream       = 0;
        xmv->video.current_frame += 1;
    }

    return 0;
}