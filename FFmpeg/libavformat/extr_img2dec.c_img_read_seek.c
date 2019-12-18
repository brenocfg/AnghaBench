#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {int img_number; scalar_t__ img_last; scalar_t__ img_first; scalar_t__ pts; int /*<<< orphan*/  loop; scalar_t__ ts_from_file; } ;
typedef  TYPE_2__ VideoDemuxData ;
struct TYPE_10__ {TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_9__ {TYPE_1__* index_entries; } ;
struct TYPE_7__ {int pos; } ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int av_index_search_timestamp (TYPE_3__*,scalar_t__,int) ; 

__attribute__((used)) static int img_read_seek(AVFormatContext *s, int stream_index, int64_t timestamp, int flags)
{
    VideoDemuxData *s1 = s->priv_data;
    AVStream *st = s->streams[0];

    if (s1->ts_from_file) {
        int index = av_index_search_timestamp(st, timestamp, flags);
        if(index < 0)
            return -1;
        s1->img_number = st->index_entries[index].pos;
        return 0;
    }

    if (timestamp < 0 || !s1->loop && timestamp > s1->img_last - s1->img_first)
        return -1;
    s1->img_number = timestamp%(s1->img_last - s1->img_first + 1) + s1->img_first;
    s1->pts = timestamp;
    return 0;
}