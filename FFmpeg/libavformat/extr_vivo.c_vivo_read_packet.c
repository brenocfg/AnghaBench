#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned int sequence; unsigned int type; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ VivoContext ;
struct TYPE_13__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_12__ {int stream_index; } ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int av_append_packet (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vivo_get_packet_header (TYPE_3__*) ; 

__attribute__((used)) static int vivo_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    VivoContext *vivo = s->priv_data;
    AVIOContext *pb = s->pb;
    unsigned old_sequence = vivo->sequence, old_type = vivo->type;
    int stream_index, ret = 0;

restart:

    if (avio_feof(pb))
        return AVERROR_EOF;

    switch (vivo->type) {
    case 0:
        avio_skip(pb, vivo->length);
        if ((ret = vivo_get_packet_header(s)) < 0)
            return ret;
        goto restart;
    case 1:
    case 2: // video
        stream_index = 0;
        break;
    case 3:
    case 4: // audio
        stream_index = 1;
        break;
    default:
        av_log(s, AV_LOG_ERROR, "unknown packet type %d\n", vivo->type);
        return AVERROR_INVALIDDATA;
    }

    if ((ret = av_get_packet(pb, pkt, vivo->length)) < 0)
        goto fail;

    // get next packet header
    if ((ret = vivo_get_packet_header(s)) < 0)
        goto fail;

    while (vivo->sequence == old_sequence &&
           (((vivo->type - 1) >> 1) == ((old_type - 1) >> 1))) {
        if (avio_feof(pb)) {
            ret = AVERROR_EOF;
            break;
        }

        if ((ret = av_append_packet(pb, pkt, vivo->length)) < 0)
            break;

        // get next packet header
        if ((ret = vivo_get_packet_header(s)) < 0)
            break;
    }

    pkt->stream_index = stream_index;

fail:
    if (ret < 0)
        av_packet_unref(pkt);
    return ret;
}