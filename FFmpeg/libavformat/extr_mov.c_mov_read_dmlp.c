#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* codecpar; } ;
struct TYPE_11__ {int size; } ;
struct TYPE_10__ {TYPE_1__* fc; } ;
struct TYPE_9__ {int frame_size; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_8__ {int nb_streams; TYPE_5__** streams; } ;
typedef  TYPE_3__ MOVContext ;
typedef  TYPE_4__ MOVAtom ;
typedef  TYPE_5__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 unsigned int avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlp_samplerate (int) ; 
 int /*<<< orphan*/  truehd_channels (int) ; 
 int /*<<< orphan*/  truehd_layout (int) ; 

__attribute__((used)) static int mov_read_dmlp(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    unsigned format_info;
    int channel_assignment, channel_assignment1, channel_assignment2;
    int ratebits;

    if (c->fc->nb_streams < 1)
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];

    if (atom.size < 10)
        return AVERROR_INVALIDDATA;

    format_info = avio_rb32(pb);

    ratebits            = (format_info >> 28) & 0xF;
    channel_assignment1 = (format_info >> 15) & 0x1F;
    channel_assignment2 = format_info & 0x1FFF;
    if (channel_assignment2)
        channel_assignment = channel_assignment2;
    else
        channel_assignment = channel_assignment1;

    st->codecpar->frame_size = 40 << (ratebits & 0x7);
    st->codecpar->sample_rate = mlp_samplerate(ratebits);
    st->codecpar->channels = truehd_channels(channel_assignment);
    st->codecpar->channel_layout = truehd_layout(channel_assignment);

    return 0;
}