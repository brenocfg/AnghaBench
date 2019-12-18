#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {TYPE_4__** streams; int /*<<< orphan*/ * pb; TYPE_3__* priv_data; } ;
struct TYPE_16__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  stream_index; int /*<<< orphan*/  size; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {TYPE_1__* codecpar; } ;
struct TYPE_14__ {size_t current_image; size_t nb_images; TYPE_2__* images; } ;
struct TYPE_13__ {int size; int nb_pal; int /*<<< orphan*/  offset; } ;
struct TYPE_12__ {scalar_t__ codec_id; int bits_per_coded_sample; } ;
typedef  TYPE_2__ IcoImage ;
typedef  TYPE_3__ IcoDemuxContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_CODEC_ID_PNG ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int AV_RL16 (int /*<<< orphan*/ *) ; 
 int AV_RL32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 int av_new_packet (TYPE_5__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 
 int avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream_put_byte (int /*<<< orphan*/ **,char) ; 
 int /*<<< orphan*/  bytestream_put_le16 (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream_put_le32 (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_packet(AVFormatContext *s, AVPacket *pkt)
{
    IcoDemuxContext *ico = s->priv_data;
    IcoImage *image;
    AVIOContext *pb = s->pb;
    AVStream *st = s->streams[0];
    int ret;

    if (ico->current_image >= ico->nb_images)
        return AVERROR_EOF;

    image = &ico->images[ico->current_image];

    if ((ret = avio_seek(pb, image->offset, SEEK_SET)) < 0)
        return ret;

    if (s->streams[ico->current_image]->codecpar->codec_id == AV_CODEC_ID_PNG) {
        if ((ret = av_get_packet(pb, pkt, image->size)) < 0)
            return ret;
    } else {
        uint8_t *buf;
        if ((ret = av_new_packet(pkt, 14 + image->size)) < 0)
            return ret;
        buf = pkt->data;

        /* add BMP header */
        bytestream_put_byte(&buf, 'B');
        bytestream_put_byte(&buf, 'M');
        bytestream_put_le32(&buf, pkt->size);
        bytestream_put_le16(&buf, 0);
        bytestream_put_le16(&buf, 0);
        bytestream_put_le32(&buf, 0);

        if ((ret = avio_read(pb, buf, image->size)) != image->size) {
            av_packet_unref(pkt);
            return ret < 0 ? ret : AVERROR_INVALIDDATA;
        }

        st->codecpar->bits_per_coded_sample = AV_RL16(buf + 14);

        if (AV_RL32(buf + 32))
            image->nb_pal = AV_RL32(buf + 32);

        if (st->codecpar->bits_per_coded_sample <= 8 && !image->nb_pal) {
            image->nb_pal = 1 << st->codecpar->bits_per_coded_sample;
            AV_WL32(buf + 32, image->nb_pal);
        }

        AV_WL32(buf - 4, 14 + 40 + image->nb_pal * 4);
        AV_WL32(buf + 8, AV_RL32(buf + 8) / 2);
    }

    pkt->stream_index = ico->current_image++;
    pkt->flags |= AV_PKT_FLAG_KEY;

    return 0;
}