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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int (* parse_packet ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ;int prev_stream_id; int prev_set_id; scalar_t__ prev_timestamp; int n_streams; int /*<<< orphan*/ * streams; int /*<<< orphan*/  dynamic_protocol_context; int /*<<< orphan*/  ic; } ;
typedef  TYPE_1__ RDTDemuxContext ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int RTP_FLAG_KEY ; 
 int ff_rdt_parse_header (int /*<<< orphan*/ *,int,int*,int*,int*,int*,scalar_t__*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

int
ff_rdt_parse_packet(RDTDemuxContext *s, AVPacket *pkt,
                    uint8_t **bufptr, int len)
{
    uint8_t *buf = bufptr ? *bufptr : NULL;
    int seq_no, flags = 0, stream_id, set_id, is_keyframe;
    uint32_t timestamp;
    int rv= 0;

    if (!s->parse_packet)
        return -1;

    if (!buf && s->prev_stream_id != -1) {
        /* return the next packets, if any */
        timestamp= 0; ///< Should not be used if buf is NULL, but should be set to the timestamp of the packet returned....
        rv= s->parse_packet(s->ic, s->dynamic_protocol_context,
                            s->streams[s->prev_stream_id],
                            pkt, &timestamp, NULL, 0, 0, flags);
        return rv;
    }

    if (len < 12)
        return -1;
    rv = ff_rdt_parse_header(buf, len, &set_id, &seq_no, &stream_id, &is_keyframe, &timestamp);
    if (rv < 0)
        return rv;
    if (is_keyframe &&
        (set_id != s->prev_set_id || timestamp != s->prev_timestamp ||
         stream_id != s->prev_stream_id)) {
        flags |= RTP_FLAG_KEY;
        s->prev_set_id    = set_id;
        s->prev_timestamp = timestamp;
    }
    s->prev_stream_id = stream_id;
    buf += rv;
    len -= rv;

     if (s->prev_stream_id >= s->n_streams) {
         s->prev_stream_id = -1;
         return -1;
     }

    rv = s->parse_packet(s->ic, s->dynamic_protocol_context,
                         s->streams[s->prev_stream_id],
                         pkt, &timestamp, buf, len, 0, flags);

    return rv;
}