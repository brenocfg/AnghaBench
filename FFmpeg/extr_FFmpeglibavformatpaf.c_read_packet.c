#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_8__ {int* data; int duration; int stream_index; int size; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int current_frame; int nb_frames; int got_audio; int audio_size; int* temp_audio_frame; int preload_count; int* blocks_count_table; size_t current_frame_block; size_t frame_blks; unsigned int* blocks_offset_table; int buffer_size; int* audio_frame; int max_audio_blks; int video_size; int* video_frame; int* frames_offset_table; } ;
typedef  TYPE_1__ PAFDemuxContext ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 int PAF_SOUND_FRAME_SIZE ; 
 int PAF_SOUND_SAMPLES ; 
 scalar_t__ av_new_packet (TYPE_2__*,int) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int read_packet(AVFormatContext *s, AVPacket *pkt)
{
    PAFDemuxContext *p  = s->priv_data;
    AVIOContext     *pb = s->pb;
    uint32_t        count, offset;
    int             size, i;

    if (p->current_frame >= p->nb_frames)
        return AVERROR_EOF;

    if (avio_feof(pb))
        return AVERROR_EOF;

    if (p->got_audio) {
        if (av_new_packet(pkt, p->audio_size) < 0)
            return AVERROR(ENOMEM);

        memcpy(pkt->data, p->temp_audio_frame, p->audio_size);
        pkt->duration     = PAF_SOUND_SAMPLES * (p->audio_size / PAF_SOUND_FRAME_SIZE);
        pkt->flags       |= AV_PKT_FLAG_KEY;
        pkt->stream_index = 1;
        p->got_audio      = 0;
        return pkt->size;
    }

    count = (p->current_frame == 0) ? p->preload_count
                                    : p->blocks_count_table[p->current_frame - 1];
    for (i = 0; i < count; i++) {
        if (p->current_frame_block >= p->frame_blks)
            return AVERROR_INVALIDDATA;

        offset = p->blocks_offset_table[p->current_frame_block] & ~(1U << 31);
        if (p->blocks_offset_table[p->current_frame_block] & (1U << 31)) {
            if (offset > p->audio_size - p->buffer_size)
                return AVERROR_INVALIDDATA;

            avio_read(pb, p->audio_frame + offset, p->buffer_size);
            if (offset == (p->max_audio_blks - 2) * p->buffer_size) {
                memcpy(p->temp_audio_frame, p->audio_frame, p->audio_size);
                p->got_audio = 1;
            }
        } else {
            if (offset > p->video_size - p->buffer_size)
                return AVERROR_INVALIDDATA;

            avio_read(pb, p->video_frame + offset, p->buffer_size);
        }
        p->current_frame_block++;
    }

    if (p->frames_offset_table[p->current_frame] >= p->video_size)
        return AVERROR_INVALIDDATA;

    size = p->video_size - p->frames_offset_table[p->current_frame];

    if (av_new_packet(pkt, size) < 0)
        return AVERROR(ENOMEM);

    pkt->stream_index = 0;
    pkt->duration     = 1;
    memcpy(pkt->data, p->video_frame + p->frames_offset_table[p->current_frame], size);
    if (pkt->data[0] & 0x20)
        pkt->flags |= AV_PKT_FLAG_KEY;
    p->current_frame++;

    return pkt->size;
}