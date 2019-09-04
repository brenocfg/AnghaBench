#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct AVFormatContext {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_6__ {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  streaminfo; } ;
typedef  TYPE_1__ FlacMuxerContext ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_DATA_NEW_EXTRADATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FLAC_STREAMINFO_SIZE ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_malloc (int) ; 
 int /*<<< orphan*/ * av_packet_get_side_data (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int flac_write_audio_packet(struct AVFormatContext *s, AVPacket *pkt)
{
    FlacMuxerContext *c = s->priv_data;
    uint8_t *streaminfo;
    int streaminfo_size;

    /* check for updated streaminfo */
    streaminfo = av_packet_get_side_data(pkt, AV_PKT_DATA_NEW_EXTRADATA,
                                         &streaminfo_size);
    if (streaminfo && streaminfo_size == FLAC_STREAMINFO_SIZE) {
        av_freep(&c->streaminfo);

        c->streaminfo = av_malloc(FLAC_STREAMINFO_SIZE);
        if (!c->streaminfo)
            return AVERROR(ENOMEM);
        memcpy(c->streaminfo, streaminfo, FLAC_STREAMINFO_SIZE);
    }

    if (pkt->size)
        avio_write(s->pb, pkt->data, pkt->size);
    return 0;
}