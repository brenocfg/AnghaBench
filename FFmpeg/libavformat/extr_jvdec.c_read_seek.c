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
typedef  int int64_t ;
struct TYPE_10__ {int /*<<< orphan*/  pb; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_9__ {int nb_index_entries; TYPE_1__* index_entries; } ;
struct TYPE_8__ {int pts; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {int /*<<< orphan*/  pos; } ;
typedef  TYPE_2__ JVDemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVSEEK_FLAG_BYTE ; 
 int AVSEEK_FLAG_FRAME ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  JV_AUDIO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_index_search_timestamp (TYPE_3__*,int,int) ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_seek(AVFormatContext *s, int stream_index,
                     int64_t ts, int flags)
{
    JVDemuxContext *jv = s->priv_data;
    AVStream *ast = s->streams[0];
    int i;

    if (flags & (AVSEEK_FLAG_BYTE | AVSEEK_FLAG_FRAME))
        return AVERROR(ENOSYS);

    switch (stream_index) {
    case 0:
        i = av_index_search_timestamp(ast, ts, flags);
        break;
    case 1:
        i = ts;
        break;
    default:
        return 0;
    }

    if (i < 0 || i >= ast->nb_index_entries)
        return 0;
    if (avio_seek(s->pb, ast->index_entries[i].pos, SEEK_SET) < 0)
        return -1;

    jv->state = JV_AUDIO;
    jv->pts   = i;
    return 0;
}