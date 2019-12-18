#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
struct ogg {int page_pos; TYPE_3__* streams; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_19__ {scalar_t__ duration; TYPE_2__** streams; TYPE_1__* internal; TYPE_13__* pb; struct ogg* priv_data; } ;
struct TYPE_18__ {int granule; int got_start; scalar_t__ codec; } ;
struct TYPE_17__ {scalar_t__ duration; scalar_t__ start_time; } ;
struct TYPE_16__ {scalar_t__ data_offset; } ;
struct TYPE_15__ {int seekable; } ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ MAX_PAGE_SIZE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_seek (TYPE_13__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_size (TYPE_13__*) ; 
 scalar_t__ ogg_calc_pts (TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ ogg_gptopts (TYPE_4__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_packet (TYPE_4__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_read_page (TYPE_4__*,int*) ; 
 int /*<<< orphan*/  ogg_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  ogg_restore (TYPE_4__*) ; 
 int ogg_save (TYPE_4__*) ; 

__attribute__((used)) static int ogg_get_length(AVFormatContext *s)
{
    struct ogg *ogg = s->priv_data;
    int i, ret;
    int64_t size, end;
    int streams_left=0;

    if (!(s->pb->seekable & AVIO_SEEKABLE_NORMAL))
        return 0;

// already set
    if (s->duration != AV_NOPTS_VALUE)
        return 0;

    size = avio_size(s->pb);
    if (size < 0)
        return 0;
    end = size > MAX_PAGE_SIZE ? size - MAX_PAGE_SIZE : 0;

    ret = ogg_save(s);
    if (ret < 0)
        return ret;
    avio_seek(s->pb, end, SEEK_SET);
    ogg->page_pos = -1;

    while (!ogg_read_page(s, &i)) {
        if (ogg->streams[i].granule != -1 && ogg->streams[i].granule != 0 &&
            ogg->streams[i].codec) {
            s->streams[i]->duration =
                ogg_gptopts(s, i, ogg->streams[i].granule, NULL);
            if (s->streams[i]->start_time != AV_NOPTS_VALUE) {
                s->streams[i]->duration -= s->streams[i]->start_time;
                streams_left-= (ogg->streams[i].got_start==-1);
                ogg->streams[i].got_start= 1;
            } else if(!ogg->streams[i].got_start) {
                ogg->streams[i].got_start= -1;
                streams_left++;
            }
        }
    }

    ogg_restore(s);

    ret = ogg_save(s);
    if (ret < 0)
        return ret;

    avio_seek (s->pb, s->internal->data_offset, SEEK_SET);
    ogg_reset(s);
    while (streams_left > 0 && !ogg_packet(s, &i, NULL, NULL, NULL)) {
        int64_t pts;
        if (i < 0) continue;
        pts = ogg_calc_pts(s, i, NULL);
        if (s->streams[i]->duration == AV_NOPTS_VALUE)
            continue;
        if (pts != AV_NOPTS_VALUE && s->streams[i]->start_time == AV_NOPTS_VALUE && !ogg->streams[i].got_start) {
            s->streams[i]->duration -= pts;
            ogg->streams[i].got_start= 1;
            streams_left--;
        }else if(s->streams[i]->start_time != AV_NOPTS_VALUE && !ogg->streams[i].got_start) {
            ogg->streams[i].got_start= 1;
            streams_left--;
        }
    }
    ogg_restore (s);

    return 0;
}