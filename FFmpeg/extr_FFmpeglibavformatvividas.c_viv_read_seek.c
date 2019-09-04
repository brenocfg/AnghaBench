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
typedef  scalar_t__ int64_t ;
struct TYPE_12__ {int n_sb_blocks; int current_sb; scalar_t__ current_sb_entry; void* audio_sample; TYPE_1__* sb_blocks; scalar_t__ sb_offset; scalar_t__ n_audio_subpackets; scalar_t__ current_audio_subpacket; } ;
typedef  TYPE_4__ VividasDemuxContext ;
struct TYPE_13__ {TYPE_3__** streams; int /*<<< orphan*/  pb; TYPE_4__* priv_data; } ;
struct TYPE_11__ {TYPE_2__* codecpar; int /*<<< orphan*/  time_base; } ;
struct TYPE_10__ {scalar_t__ sample_rate; } ;
struct TYPE_9__ {scalar_t__ packet_offset; scalar_t__ n_packets; scalar_t__ byte_offset; } ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_inv_q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_make_q (scalar_t__,int) ; 
 void* av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_sb_block (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int viv_read_seek(AVFormatContext *s, int stream_index, int64_t timestamp, int flags)
{
    VividasDemuxContext *viv = s->priv_data;
    int64_t frame;

    if (stream_index == 0)
        frame = timestamp;
    else
        frame = av_rescale_q(timestamp, s->streams[0]->time_base, s->streams[stream_index]->time_base);

    for (int i = 0; i < viv->n_sb_blocks; i++) {
        if (frame >= viv->sb_blocks[i].packet_offset && frame < viv->sb_blocks[i].packet_offset + viv->sb_blocks[i].n_packets) {
            // flush audio packet queue
            viv->current_audio_subpacket = 0;
            viv->n_audio_subpackets = 0;
            viv->current_sb = i;
            // seek to ith sb block
            avio_seek(s->pb, viv->sb_offset + viv->sb_blocks[i].byte_offset, SEEK_SET);
            // load the block
            load_sb_block(s, viv, 0);
            // most problematic part: guess audio offset
            viv->audio_sample = av_rescale_q(viv->sb_blocks[i].packet_offset, av_make_q(s->streams[1]->codecpar->sample_rate, 1), av_inv_q(s->streams[0]->time_base));
            // hand-tuned 1.s a/v offset
            viv->audio_sample += s->streams[1]->codecpar->sample_rate;
            viv->current_sb_entry = 0;
            return 1;
        }
    }
    return 0;
}