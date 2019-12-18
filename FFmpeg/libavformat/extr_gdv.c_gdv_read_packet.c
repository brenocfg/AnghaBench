#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_16__ {TYPE_3__* pb; TYPE_1__* priv_data; } ;
struct TYPE_15__ {int error; } ;
struct TYPE_14__ {int stream_index; int /*<<< orphan*/  flags; } ;
struct TYPE_13__ {int audio_size; int is_audio; scalar_t__ is_first_video; int /*<<< orphan*/  pal; } ;
typedef  TYPE_1__ GDVContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVPALETTE_SIZE ; 
 int /*<<< orphan*/  AV_PKT_DATA_PALETTE ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_get_packet (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 scalar_t__ avio_feof (TYPE_3__*) ; 
 int avio_rl16 (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gdv_read_packet(AVFormatContext *ctx, AVPacket *pkt)
{
    GDVContext *gdv = ctx->priv_data;
    AVIOContext *pb = ctx->pb;
    int ret;

    if (avio_feof(pb))
        return pb->error ? pb->error : AVERROR_EOF;

    if (gdv->audio_size && gdv->is_audio) {
        ret = av_get_packet(pb, pkt, gdv->audio_size);
        if (ret < 0)
            return ret;
        pkt->stream_index = 1;
        gdv->is_audio = 0;
    } else {
        uint8_t *pal;

        if (avio_rl16(pb) != 0x1305)
            return AVERROR_INVALIDDATA;
        ret = av_get_packet(pb, pkt, 4 + avio_rl16(pb));
        if (ret < 0)
            return ret;
        pkt->stream_index = 0;
        gdv->is_audio = 1;

        if (gdv->is_first_video) {
            pal = av_packet_new_side_data(pkt, AV_PKT_DATA_PALETTE,
                                          AVPALETTE_SIZE);
            if (!pal) {
                av_packet_unref(pkt);
                return AVERROR(ENOMEM);
            }
            memcpy(pal, gdv->pal, AVPALETTE_SIZE);
            pkt->flags |= AV_PKT_FLAG_KEY;
            gdv->is_first_video = 0;
        }
    }

    return 0;
}