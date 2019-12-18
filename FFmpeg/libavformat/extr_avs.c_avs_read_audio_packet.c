#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  index; } ;
struct TYPE_11__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  stream_index; } ;
struct TYPE_9__ {int remaining_audio_size; TYPE_6__* st_audio; } ;
typedef  TYPE_1__ AvsFormat ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EIO ; 
 int avio_tell (int /*<<< orphan*/ ) ; 
 int ff_voc_get_packet (TYPE_3__*,TYPE_2__*,TYPE_6__*,int) ; 

__attribute__((used)) static int avs_read_audio_packet(AVFormatContext * s, AVPacket * pkt)
{
    AvsFormat *avs = s->priv_data;
    int ret, size;

    size = avio_tell(s->pb);
    ret = ff_voc_get_packet(s, pkt, avs->st_audio, avs->remaining_audio_size);
    size = avio_tell(s->pb) - size;
    avs->remaining_audio_size -= size;

    if (ret == AVERROR(EIO))
        return 0;    /* this indicate EOS */
    if (ret < 0)
        return ret;

    pkt->stream_index = avs->st_audio->index;
    pkt->flags |= AV_PKT_FLAG_KEY;

    return size;
}