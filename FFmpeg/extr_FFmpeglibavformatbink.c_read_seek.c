#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_11__ {int seekable; } ;
struct TYPE_10__ {TYPE_6__* pb; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_9__ {TYPE_1__* index_entries; } ;
struct TYPE_8__ {int current_track; int /*<<< orphan*/  audio_pts; scalar_t__ video_pts; scalar_t__ smush_size; } ;
struct TYPE_7__ {scalar_t__ pos; } ;
typedef  TYPE_2__ BinkDemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ avio_seek (TYPE_6__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_seek(AVFormatContext *s, int stream_index, int64_t timestamp, int flags)
{
    BinkDemuxContext *bink = s->priv_data;
    AVStream *vst = s->streams[0];

    if (!(s->pb->seekable & AVIO_SEEKABLE_NORMAL))
        return -1;

    /* seek to the first frame */
    if (avio_seek(s->pb, vst->index_entries[0].pos + bink->smush_size, SEEK_SET) < 0)
        return -1;

    bink->video_pts = 0;
    memset(bink->audio_pts, 0, sizeof(bink->audio_pts));
    bink->current_track = -1;
    return 0;
}