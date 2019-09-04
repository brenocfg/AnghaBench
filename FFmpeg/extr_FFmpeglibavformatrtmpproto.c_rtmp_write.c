#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  commandbuffer ;
struct TYPE_19__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_22__ {int type; int /*<<< orphan*/ * data; scalar_t__ size; int /*<<< orphan*/  extra; } ;
struct TYPE_21__ {int skip_bytes; scalar_t__ flv_header_bytes; int flv_size; scalar_t__ flv_off; scalar_t__ flv_nb_packets; scalar_t__ flush_interval; int /*<<< orphan*/ * nb_prev_pkt; TYPE_13__** prev_pkt; int /*<<< orphan*/  in_chunk_size; TYPE_10__* stream; TYPE_6__ out_pkt; int /*<<< orphan*/ * flv_data; int /*<<< orphan*/  stream_id; int /*<<< orphan*/ * flv_header; } ;
struct TYPE_20__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_18__ {scalar_t__ channel_id; } ;
struct TYPE_17__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ RTMPPacket ;
typedef  TYPE_3__ RTMPContext ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIO_FLAG_NONBLOCK ; 
 int /*<<< orphan*/  EAGAIN ; 
 int FFMIN (scalar_t__,int) ; 
 int RTMP_AUDIO_CHANNEL ; 
 scalar_t__ RTMP_HEADER ; 
 int RTMP_PT_AUDIO ; 
 int RTMP_PT_NOTIFY ; 
 int RTMP_PT_VIDEO ; 
 int RTMP_VIDEO_CHANNEL ; 
 int av_reallocp (int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int bytestream_get_be24 (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  bytestream_get_buffer (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int) ; 
 int bytestream_get_byte (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  ff_amf_read_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  ff_amf_write_string (int /*<<< orphan*/ **,char*) ; 
 int ff_rtmp_check_alloc_array (TYPE_13__**,int /*<<< orphan*/ *,int) ; 
 int ff_rtmp_packet_create (TYPE_6__*,int,int,int,int) ; 
 int /*<<< orphan*/  ff_rtmp_packet_destroy (TYPE_2__*) ; 
 int ff_rtmp_packet_read_internal (TYPE_10__*,TYPE_2__*,int /*<<< orphan*/ ,TYPE_13__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ffurl_read (TYPE_10__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int rtmp_parse_result (TYPE_1__*,TYPE_3__*,TYPE_2__*) ; 
 int rtmp_send_packet (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int rtmp_write(URLContext *s, const uint8_t *buf, int size)
{
    RTMPContext *rt = s->priv_data;
    int size_temp = size;
    int pktsize, pkttype, copy;
    uint32_t ts;
    const uint8_t *buf_temp = buf;
    uint8_t c;
    int ret;

    do {
        if (rt->skip_bytes) {
            int skip = FFMIN(rt->skip_bytes, size_temp);
            buf_temp       += skip;
            size_temp      -= skip;
            rt->skip_bytes -= skip;
            continue;
        }

        if (rt->flv_header_bytes < RTMP_HEADER) {
            const uint8_t *header = rt->flv_header;
            int channel = RTMP_AUDIO_CHANNEL;

            copy = FFMIN(RTMP_HEADER - rt->flv_header_bytes, size_temp);
            bytestream_get_buffer(&buf_temp, rt->flv_header + rt->flv_header_bytes, copy);
            rt->flv_header_bytes += copy;
            size_temp            -= copy;
            if (rt->flv_header_bytes < RTMP_HEADER)
                break;

            pkttype = bytestream_get_byte(&header);
            pktsize = bytestream_get_be24(&header);
            ts = bytestream_get_be24(&header);
            ts |= bytestream_get_byte(&header) << 24;
            bytestream_get_be24(&header);
            rt->flv_size = pktsize;

            if (pkttype == RTMP_PT_VIDEO)
                channel = RTMP_VIDEO_CHANNEL;

            if (((pkttype == RTMP_PT_VIDEO || pkttype == RTMP_PT_AUDIO) && ts == 0) ||
                pkttype == RTMP_PT_NOTIFY) {
                if ((ret = ff_rtmp_check_alloc_array(&rt->prev_pkt[1],
                                                     &rt->nb_prev_pkt[1],
                                                     channel)) < 0)
                    return ret;
                // Force sending a full 12 bytes header by clearing the
                // channel id, to make it not match a potential earlier
                // packet in the same channel.
                rt->prev_pkt[1][channel].channel_id = 0;
            }

            //this can be a big packet, it's better to send it right here
            if ((ret = ff_rtmp_packet_create(&rt->out_pkt, channel,
                                             pkttype, ts, pktsize)) < 0)
                return ret;

            rt->out_pkt.extra = rt->stream_id;
            rt->flv_data = rt->out_pkt.data;
        }

        copy = FFMIN(rt->flv_size - rt->flv_off, size_temp);
        bytestream_get_buffer(&buf_temp, rt->flv_data + rt->flv_off, copy);
        rt->flv_off += copy;
        size_temp   -= copy;

        if (rt->flv_off == rt->flv_size) {
            rt->skip_bytes = 4;

            if (rt->out_pkt.type == RTMP_PT_NOTIFY) {
                // For onMetaData and |RtmpSampleAccess packets, we want
                // @setDataFrame prepended to the packet before it gets sent.
                // However, not all RTMP_PT_NOTIFY packets (e.g., onTextData
                // and onCuePoint).
                uint8_t commandbuffer[64];
                int stringlen = 0;
                GetByteContext gbc;

                bytestream2_init(&gbc, rt->flv_data, rt->flv_size);
                if (!ff_amf_read_string(&gbc, commandbuffer, sizeof(commandbuffer),
                                        &stringlen)) {
                    if (!strcmp(commandbuffer, "onMetaData") ||
                        !strcmp(commandbuffer, "|RtmpSampleAccess")) {
                        uint8_t *ptr;
                        if ((ret = av_reallocp(&rt->out_pkt.data, rt->out_pkt.size + 16)) < 0) {
                            rt->flv_size = rt->flv_off = rt->flv_header_bytes = 0;
                            return ret;
                        }
                        memmove(rt->out_pkt.data + 16, rt->out_pkt.data, rt->out_pkt.size);
                        rt->out_pkt.size += 16;
                        ptr = rt->out_pkt.data;
                        ff_amf_write_string(&ptr, "@setDataFrame");
                    }
                }
            }

            if ((ret = rtmp_send_packet(rt, &rt->out_pkt, 0)) < 0)
                return ret;
            rt->flv_size = 0;
            rt->flv_off = 0;
            rt->flv_header_bytes = 0;
            rt->flv_nb_packets++;
        }
    } while (buf_temp - buf < size);

    if (rt->flv_nb_packets < rt->flush_interval)
        return size;
    rt->flv_nb_packets = 0;

    /* set stream into nonblocking mode */
    rt->stream->flags |= AVIO_FLAG_NONBLOCK;

    /* try to read one byte from the stream */
    ret = ffurl_read(rt->stream, &c, 1);

    /* switch the stream back into blocking mode */
    rt->stream->flags &= ~AVIO_FLAG_NONBLOCK;

    if (ret == AVERROR(EAGAIN)) {
        /* no incoming data to handle */
        return size;
    } else if (ret < 0) {
        return ret;
    } else if (ret == 1) {
        RTMPPacket rpkt = { 0 };

        if ((ret = ff_rtmp_packet_read_internal(rt->stream, &rpkt,
                                                rt->in_chunk_size,
                                                &rt->prev_pkt[0],
                                                &rt->nb_prev_pkt[0], c)) <= 0)
             return ret;

        if ((ret = rtmp_parse_result(s, rt, &rpkt)) < 0)
            return ret;

        ff_rtmp_packet_destroy(&rpkt);
    }

    return size;
}