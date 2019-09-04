#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nb_streams; TYPE_1__** streams; TYPE_3__* priv_data; } ;
struct TYPE_8__ {scalar_t__ is_dvd; } ;
struct TYPE_7__ {int id; } ;
struct TYPE_6__ {TYPE_2__* priv_data; } ;
typedef  TYPE_2__ StreamInfo ;
typedef  TYPE_3__ MpegMuxContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */

__attribute__((used)) static int get_system_header_size(AVFormatContext *ctx)
{
    int buf_index, i, private_stream_coded;
    StreamInfo *stream;
    MpegMuxContext *s = ctx->priv_data;

    if (s->is_dvd)
        return 18; // DVD-Video system headers are 18 bytes fixed length.

    buf_index = 12;
    private_stream_coded = 0;
    for (i = 0; i < ctx->nb_streams; i++) {
        stream = ctx->streams[i]->priv_data;
        if (stream->id < 0xc0) {
            if (private_stream_coded)
                continue;
            private_stream_coded = 1;
        }
        buf_index += 3;
    }
    return buf_index;
}