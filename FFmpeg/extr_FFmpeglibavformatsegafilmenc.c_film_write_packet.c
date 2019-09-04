#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_15__ {TYPE_2__** streams; TYPE_4__* priv_data; int /*<<< orphan*/ * pb; } ;
struct TYPE_14__ {scalar_t__ stream_index; int flags; int size; int /*<<< orphan*/ * data; int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; } ;
struct TYPE_13__ {scalar_t__ audio_index; TYPE_3__* last; int /*<<< orphan*/  packet_count; TYPE_3__* start; } ;
struct TYPE_12__ {int audio; int keyframe; int size; int index; struct TYPE_12__* next; int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; } ;
struct TYPE_11__ {TYPE_1__* codecpar; } ;
struct TYPE_10__ {int codec_id; } ;
typedef  TYPE_3__ FILMPacket ;
typedef  TYPE_4__ FILMOutputContext ;
typedef  TYPE_5__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_CODEC_ID_CINEPAK ; 
 int AV_PKT_FLAG_KEY ; 
 int AV_RB24 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_WB24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_3__* av_mallocz (int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int film_write_packet(AVFormatContext *format_context, AVPacket *pkt)
{
    FILMPacket *metadata;
    AVIOContext *pb = format_context->pb;
    FILMOutputContext *film = format_context->priv_data;
    int encoded_buf_size = 0;
    enum AVCodecID codec_id;

    /* Track the metadata used to write the header and add it to the linked list */
    metadata = av_mallocz(sizeof(FILMPacket));
    if (!metadata)
        return AVERROR(ENOMEM);
    metadata->audio = pkt->stream_index == film->audio_index;
    metadata->keyframe = pkt->flags & AV_PKT_FLAG_KEY;
    metadata->pts = pkt->pts;
    metadata->duration = pkt->duration;
    metadata->size = pkt->size;
    if (film->last == NULL) {
        metadata->index = 0;
    } else {
        metadata->index = film->last->index + film->last->size;
        film->last->next = metadata;
    }
    metadata->next = NULL;
    if (film->start == NULL)
        film->start = metadata;
    film->packet_count++;
    film->last = metadata;

    codec_id = format_context->streams[pkt->stream_index]->codecpar->codec_id;

    /* Sega Cinepak has an extra two-byte header; write dummy data there,
     * then adjust the cvid header to accommodate for the extra size */
    if (codec_id == AV_CODEC_ID_CINEPAK) {
        encoded_buf_size = AV_RB24(&pkt->data[1]);
        /* Already Sega Cinepak, so no need to reformat the packets */
        if (encoded_buf_size != pkt->size && (pkt->size % encoded_buf_size) != 0) {
            avio_write(pb, pkt->data, pkt->size);
        } else {
            uint8_t padding[2] = {0, 0};
            /* In Sega Cinepak, the reported size in the Cinepak header is
             * 8 bytes too short. However, the size in the STAB section of the header
             * is correct, taking into account the extra two bytes. */
            AV_WB24(&pkt->data[1], pkt->size - 8 + 2);
            metadata->size += 2;

            avio_write(pb, pkt->data, 10);
            avio_write(pb, padding, 2);
            avio_write(pb, &pkt->data[10], pkt->size - 10);
        }
    } else {
        /* Other formats can just be written as-is */
        avio_write(pb, pkt->data, pkt->size);
    }

    return 0;
}