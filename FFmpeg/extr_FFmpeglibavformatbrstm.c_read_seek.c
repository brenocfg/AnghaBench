#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {int /*<<< orphan*/  pb; TYPE_2__* priv_data; TYPE_3__** streams; } ;
struct TYPE_10__ {TYPE_1__* codecpar; } ;
struct TYPE_9__ {scalar_t__ samples_per_block; scalar_t__ block_size; scalar_t__ current_block; scalar_t__ data_start; } ;
struct TYPE_8__ {scalar_t__ channels; } ;
typedef  TYPE_2__ BRSTMDemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_update_cur_dts (TYPE_4__*,TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static int read_seek(AVFormatContext *s, int stream_index,
                     int64_t timestamp, int flags)
{
    AVStream *st = s->streams[stream_index];
    BRSTMDemuxContext *b = s->priv_data;
    int64_t ret = 0;

    timestamp /= b->samples_per_block;
    ret = avio_seek(s->pb, b->data_start + timestamp * b->block_size *
                           st->codecpar->channels, SEEK_SET);
    if (ret < 0)
        return ret;

    b->current_block = timestamp;
    ff_update_cur_dts(s, st, timestamp * b->samples_per_block);
    return 0;
}