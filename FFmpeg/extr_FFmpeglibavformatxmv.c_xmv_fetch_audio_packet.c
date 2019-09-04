#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_9__ {scalar_t__ current_frame; scalar_t__ frame_count; } ;
struct TYPE_10__ {TYPE_1__ video; TYPE_3__* audio; } ;
typedef  TYPE_2__ XMVDemuxContext ;
struct TYPE_11__ {scalar_t__ data_offset; size_t data_size; size_t block_align; size_t block_count; int /*<<< orphan*/  stream_index; int /*<<< orphan*/  frame_size; } ;
typedef  TYPE_3__ XMVAudioPacket ;
struct TYPE_13__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_12__ {size_t duration; size_t pts; int /*<<< orphan*/  dts; int /*<<< orphan*/  stream_index; } ;
typedef  TYPE_4__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  EIO ; 
 size_t FFMIN (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_4__*,size_t) ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xmv_fetch_audio_packet(AVFormatContext *s,
                                  AVPacket *pkt, uint32_t stream)
{
    XMVDemuxContext *xmv   = s->priv_data;
    AVIOContext     *pb    = s->pb;
    XMVAudioPacket  *audio = &xmv->audio[stream];

    uint32_t data_size;
    uint32_t block_count;
    int result;

    /* Seek to it */
    if (avio_seek(pb, audio->data_offset, SEEK_SET) != audio->data_offset)
        return AVERROR(EIO);

    if ((xmv->video.current_frame + 1) < xmv->video.frame_count)
        /* Not the last frame, get at most frame_size bytes. */
        data_size = FFMIN(audio->frame_size, audio->data_size);
    else
        /* Last frame, get the rest. */
        data_size = audio->data_size;

    /* Read the packet */
    result = av_get_packet(pb, pkt, data_size);
    if (result <= 0)
        return result;

    pkt->stream_index = audio->stream_index;

    /* Calculate the PTS */

    block_count = data_size / audio->block_align;

    pkt->duration = block_count;
    pkt->pts      = audio->block_count;
    pkt->dts      = AV_NOPTS_VALUE;

    audio->block_count += block_count;

    /* Advance offset */
    audio->data_size   -= data_size;
    audio->data_offset += data_size;

    return 0;
}