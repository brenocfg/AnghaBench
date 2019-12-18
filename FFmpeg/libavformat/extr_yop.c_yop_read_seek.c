#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_6__ {int frame_size; int odd_frame; int /*<<< orphan*/  video_packet; } ;
typedef  TYPE_2__ YopDecContext ;
struct TYPE_7__ {int /*<<< orphan*/  pb; TYPE_1__* internal; TYPE_2__* priv_data; } ;
struct TYPE_5__ {int data_offset; } ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int FFMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FFMIN (int,int) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int avio_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int yop_read_seek(AVFormatContext *s, int stream_index,
                         int64_t timestamp, int flags)
{
    YopDecContext *yop = s->priv_data;
    int64_t frame_pos, pos_min, pos_max;
    int frame_count;

    if (!stream_index)
        return -1;

    pos_min        = s->internal->data_offset;
    pos_max        = avio_size(s->pb) - yop->frame_size;
    frame_count    = (pos_max - pos_min) / yop->frame_size;

    timestamp      = FFMAX(0, FFMIN(frame_count, timestamp));

    frame_pos      = timestamp * yop->frame_size + pos_min;

    if (avio_seek(s->pb, frame_pos, SEEK_SET) < 0)
        return -1;

    av_packet_unref(&yop->video_packet);
    yop->odd_frame = timestamp & 1;

    return 0;
}