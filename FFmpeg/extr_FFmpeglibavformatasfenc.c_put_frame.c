#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* int64_t ;
struct TYPE_16__ {int packet_timestamp_start; int packet_size; int multi_payloads_present; int packet_size_left; scalar_t__ packet_nb_payloads; void* packet_timestamp_end; int /*<<< orphan*/  pb; } ;
struct TYPE_15__ {int /*<<< orphan*/  seq; } ;
struct TYPE_14__ {TYPE_5__* priv_data; } ;
struct TYPE_13__ {TYPE_1__* codecpar; } ;
struct TYPE_12__ {scalar_t__ codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ ASFStream ;
typedef  TYPE_5__ ASFContext ;

/* Variables and functions */
 scalar_t__ ASF_PAYLOADS_PER_PACKET ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 void* INT64_MAX ; 
 int MULTI_PAYLOAD_HEADERS ; 
 int PACKET_HEADER_MIN_SIZE ; 
 int PAYLOAD_HEADER_SIZE_MULTIPLE_PAYLOADS ; 
 int PAYLOAD_HEADER_SIZE_SINGLE_PAYLOAD ; 
 scalar_t__ PREROLL_TIME ; 
 int SINGLE_PAYLOAD_HEADERS ; 
 void* UINT16_MAX ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  flush_packet (TYPE_3__*) ; 
 int /*<<< orphan*/  put_payload_header (TYPE_3__*,TYPE_4__*,scalar_t__,int,int,int,int) ; 

__attribute__((used)) static void put_frame(AVFormatContext *s, ASFStream *stream, AVStream *avst,
                      int64_t timestamp, const uint8_t *buf,
                      int m_obj_size, int flags)
{
    ASFContext *asf = s->priv_data;
    int m_obj_offset, payload_len, frag_len1;

    m_obj_offset = 0;
    while (m_obj_offset < m_obj_size) {
        payload_len = m_obj_size - m_obj_offset;
        if (asf->packet_timestamp_start == -1) {
            const int multi_payload_constant = (asf->packet_size - MULTI_PAYLOAD_HEADERS);
            asf->multi_payloads_present = (payload_len < multi_payload_constant);

            asf->packet_size_left = asf->packet_size;
            if (asf->multi_payloads_present) {
                frag_len1 = multi_payload_constant - 1;
            } else {
                frag_len1 = asf->packet_size - SINGLE_PAYLOAD_HEADERS;
            }
            asf->packet_timestamp_start = timestamp;
        } else {
            // multi payloads
            frag_len1 = asf->packet_size_left -
                        PAYLOAD_HEADER_SIZE_MULTIPLE_PAYLOADS -
                        PACKET_HEADER_MIN_SIZE - 1;

            if (frag_len1 < payload_len &&
                avst->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
                flush_packet(s);
                continue;
            }
            if (asf->packet_timestamp_start > INT64_MAX - UINT16_MAX ||
                timestamp > asf->packet_timestamp_start + UINT16_MAX) {
                flush_packet(s);
                continue;
            }
        }
        if (frag_len1 > 0) {
            if (payload_len > frag_len1)
                payload_len = frag_len1;
            else if (payload_len == (frag_len1 - 1))
                payload_len = frag_len1 - 2;  // additional byte need to put padding length

            put_payload_header(s, stream, timestamp + PREROLL_TIME,
                               m_obj_size, m_obj_offset, payload_len, flags);
            avio_write(&asf->pb, buf, payload_len);

            if (asf->multi_payloads_present)
                asf->packet_size_left -= (payload_len + PAYLOAD_HEADER_SIZE_MULTIPLE_PAYLOADS);
            else
                asf->packet_size_left -= (payload_len + PAYLOAD_HEADER_SIZE_SINGLE_PAYLOAD);
            asf->packet_timestamp_end = timestamp;

            asf->packet_nb_payloads++;
        } else {
            payload_len = 0;
        }
        m_obj_offset += payload_len;
        buf          += payload_len;

        if (!asf->multi_payloads_present)
            flush_packet(s);
        else if (asf->packet_size_left <= (PAYLOAD_HEADER_SIZE_MULTIPLE_PAYLOADS + PACKET_HEADER_MIN_SIZE + 1))
            flush_packet(s);
        else if (asf->packet_nb_payloads == ASF_PAYLOADS_PER_PACKET)
            flush_packet(s);
    }
    stream->seq++;
}