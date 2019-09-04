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
struct TYPE_10__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_9__ {unsigned char* data; void* pos; int /*<<< orphan*/  stream_index; scalar_t__ pts; } ;
struct TYPE_8__ {int /*<<< orphan*/  audio_stream_index; int /*<<< orphan*/  frame_number; int /*<<< orphan*/  video_stream_index; } ;
typedef  TYPE_1__ FlicDemuxContext ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AV_RL16 (unsigned char*) ; 
 unsigned int AV_RL32 (unsigned char*) ; 
 int /*<<< orphan*/  EIO ; 
 int FLIC_CHUNK_MAGIC_1 ; 
 int FLIC_CHUNK_MAGIC_2 ; 
 int FLIC_PREAMBLE_SIZE ; 
 int FLIC_TFTD_CHUNK_AUDIO ; 
 scalar_t__ av_new_packet (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,unsigned int) ; 
 void* avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static int flic_read_packet(AVFormatContext *s,
                            AVPacket *pkt)
{
    FlicDemuxContext *flic = s->priv_data;
    AVIOContext *pb = s->pb;
    int packet_read = 0;
    unsigned int size;
    int magic;
    int ret = 0;
    unsigned char preamble[FLIC_PREAMBLE_SIZE];

    while (!packet_read && !avio_feof(pb)) {

        if ((ret = avio_read(pb, preamble, FLIC_PREAMBLE_SIZE)) !=
            FLIC_PREAMBLE_SIZE) {
            ret = AVERROR(EIO);
            break;
        }

        size = AV_RL32(&preamble[0]);
        magic = AV_RL16(&preamble[4]);

        if (((magic == FLIC_CHUNK_MAGIC_1) || (magic == FLIC_CHUNK_MAGIC_2)) && size > FLIC_PREAMBLE_SIZE) {
            if (av_new_packet(pkt, size)) {
                ret = AVERROR(EIO);
                break;
            }
            pkt->stream_index = flic->video_stream_index;
            pkt->pts = flic->frame_number++;
            pkt->pos = avio_tell(pb);
            memcpy(pkt->data, preamble, FLIC_PREAMBLE_SIZE);
            ret = avio_read(pb, pkt->data + FLIC_PREAMBLE_SIZE,
                size - FLIC_PREAMBLE_SIZE);
            if (ret != size - FLIC_PREAMBLE_SIZE) {
                av_packet_unref(pkt);
                ret = AVERROR(EIO);
            }
            packet_read = 1;
        } else if (magic == FLIC_TFTD_CHUNK_AUDIO) {
            if (av_new_packet(pkt, size)) {
                ret = AVERROR(EIO);
                break;
            }

            /* skip useless 10B sub-header (yes, it's not accounted for in the chunk header) */
            avio_skip(pb, 10);

            pkt->stream_index = flic->audio_stream_index;
            pkt->pos = avio_tell(pb);
            ret = avio_read(pb, pkt->data, size);

            if (ret != size) {
                av_packet_unref(pkt);
                ret = AVERROR(EIO);
            }

            packet_read = 1;
        } else {
            /* not interested in this chunk */
            avio_skip(pb, size - 6);
        }
    }

    return avio_feof(pb) ? AVERROR_EOF : ret;
}