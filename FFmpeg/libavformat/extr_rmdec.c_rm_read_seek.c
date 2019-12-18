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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {scalar_t__ audio_pkt_cnt; } ;
typedef  TYPE_1__ RMDemuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ ff_seek_frame_binary (TYPE_2__*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rm_read_seek(AVFormatContext *s, int stream_index,
                        int64_t pts, int flags)
{
    RMDemuxContext *rm = s->priv_data;

    if (ff_seek_frame_binary(s, stream_index, pts, flags) < 0)
        return -1;
    rm->audio_pkt_cnt = 0;
    return 0;
}