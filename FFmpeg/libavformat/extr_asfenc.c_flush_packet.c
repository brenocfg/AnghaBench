#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int packet_timestamp_end; int packet_timestamp_start; int packet_size_left; int packet_size; scalar_t__ packet_buf; int /*<<< orphan*/  pb; scalar_t__ packet_nb_payloads; int /*<<< orphan*/  nb_packets; scalar_t__ is_streamed; } ;
struct TYPE_6__ {scalar_t__ packet_size; int /*<<< orphan*/  pb; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ ASFContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ffio_init_context (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_chunk (TYPE_1__*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int put_payload_parsing_info (TYPE_1__*,int,int,scalar_t__,int) ; 

__attribute__((used)) static void flush_packet(AVFormatContext *s)
{
    ASFContext *asf = s->priv_data;
    int packet_hdr_size, packet_filled_size;

    av_assert0(asf->packet_timestamp_end >= asf->packet_timestamp_start);

    if (asf->is_streamed)
        put_chunk(s, 0x4424, s->packet_size, 0);

    packet_hdr_size = put_payload_parsing_info(s,
                                               asf->packet_timestamp_start,
                                               asf->packet_timestamp_end - asf->packet_timestamp_start,
                                               asf->packet_nb_payloads,
                                               asf->packet_size_left);

    packet_filled_size = asf->packet_size - asf->packet_size_left;
    av_assert0(packet_hdr_size <= asf->packet_size_left);
    memset(asf->packet_buf + packet_filled_size, 0, asf->packet_size_left);

    avio_write(s->pb, asf->packet_buf, s->packet_size - packet_hdr_size);

    avio_flush(s->pb);
    asf->nb_packets++;
    asf->packet_nb_payloads     = 0;
    asf->packet_timestamp_start = -1;
    asf->packet_timestamp_end   = -1;
    ffio_init_context(&asf->pb, asf->packet_buf, s->packet_size, 1,
                      NULL, NULL, NULL, NULL);
}