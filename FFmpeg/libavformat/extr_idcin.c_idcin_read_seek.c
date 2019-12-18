#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {int /*<<< orphan*/ * streams; int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_5__ {scalar_t__ first_pkt_pos; size_t video_stream_index; int next_chunk_is_video; scalar_t__ current_audio_chunk; } ;
typedef  TYPE_1__ IdcinDemuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_update_cur_dts (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int idcin_read_seek(AVFormatContext *s, int stream_index,
                           int64_t timestamp, int flags)
{
    IdcinDemuxContext *idcin = s->priv_data;

    if (idcin->first_pkt_pos > 0) {
        int64_t ret = avio_seek(s->pb, idcin->first_pkt_pos, SEEK_SET);
        if (ret < 0)
            return ret;
        ff_update_cur_dts(s, s->streams[idcin->video_stream_index], 0);
        idcin->next_chunk_is_video = 1;
        idcin->current_audio_chunk = 0;
        return 0;
    }
    return -1;
}