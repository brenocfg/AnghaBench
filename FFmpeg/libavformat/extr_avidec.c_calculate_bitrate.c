#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_13__ {int nb_streams; TYPE_4__** streams; TYPE_5__* priv_data; } ;
struct TYPE_12__ {int io_fsize; } ;
struct TYPE_9__ {int num; int /*<<< orphan*/  den; } ;
struct TYPE_11__ {int nb_index_entries; TYPE_3__* codecpar; TYPE_2__ time_base; TYPE_1__* index_entries; } ;
struct TYPE_10__ {scalar_t__ bit_rate; } ;
struct TYPE_8__ {int size; int timestamp; int /*<<< orphan*/  pos; } ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVIContext ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int av_rescale (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int calculate_bitrate(AVFormatContext *s)
{
    AVIContext *avi = s->priv_data;
    int i, j;
    int64_t lensum = 0;
    int64_t maxpos = 0;

    for (i = 0; i<s->nb_streams; i++) {
        int64_t len = 0;
        AVStream *st = s->streams[i];

        if (!st->nb_index_entries)
            continue;

        for (j = 0; j < st->nb_index_entries; j++)
            len += st->index_entries[j].size;
        maxpos = FFMAX(maxpos, st->index_entries[j-1].pos);
        lensum += len;
    }
    if (maxpos < avi->io_fsize*9/10) // index does not cover the whole file
        return 0;
    if (lensum*9/10 > maxpos || lensum < maxpos*9/10) // frame sum and filesize mismatch
        return 0;

    for (i = 0; i<s->nb_streams; i++) {
        int64_t len = 0;
        AVStream *st = s->streams[i];
        int64_t duration;
        int64_t bitrate;

        for (j = 0; j < st->nb_index_entries; j++)
            len += st->index_entries[j].size;

        if (st->nb_index_entries < 2 || st->codecpar->bit_rate > 0)
            continue;
        duration = st->index_entries[j-1].timestamp - st->index_entries[0].timestamp;
        bitrate = av_rescale(8*len, st->time_base.den, duration * st->time_base.num);
        if (bitrate > 0) {
            st->codecpar->bit_rate = bitrate;
        }
    }
    return 1;
}