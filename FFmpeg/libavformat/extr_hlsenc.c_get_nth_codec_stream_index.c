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
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_7__ {int nb_streams; TYPE_2__** streams; } ;
struct TYPE_6__ {TYPE_1__* codecpar; } ;
struct TYPE_5__ {int codec_type; } ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */

__attribute__((used)) static int get_nth_codec_stream_index(AVFormatContext *s,
                                      enum AVMediaType codec_type,
                                      int stream_id)
{
    unsigned int stream_index, cnt;
    if (stream_id < 0 || stream_id > s->nb_streams - 1)
        return -1;
    cnt = 0;
    for (stream_index = 0; stream_index < s->nb_streams; stream_index++) {
        if (s->streams[stream_index]->codecpar->codec_type != codec_type)
            continue;
        if (cnt == stream_id)
            return stream_index;
        cnt++;
    }
    return -1;
}