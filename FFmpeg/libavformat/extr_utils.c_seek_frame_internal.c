#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_15__ {TYPE_2__* iformat; TYPE_3__** streams; } ;
struct TYPE_12__ {scalar_t__ num; int /*<<< orphan*/  den; } ;
struct TYPE_14__ {TYPE_1__ time_base; } ;
struct TYPE_13__ {int flags; int (* read_seek ) (TYPE_4__*,int,int,int) ;scalar_t__ read_timestamp; } ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVFMT_NOBINSEARCH ; 
 int AVFMT_NOGENSEARCH ; 
 int AVFMT_NO_BYTE_SEEK ; 
 int AVSEEK_FLAG_BYTE ; 
 int AV_TIME_BASE ; 
 int av_find_default_stream_index (TYPE_4__*) ; 
 int av_rescale (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_read_frame_flush (TYPE_4__*) ; 
 int ff_seek_frame_binary (TYPE_4__*,int,int,int) ; 
 int seek_frame_byte (TYPE_4__*,int,int,int) ; 
 int seek_frame_generic (TYPE_4__*,int,int,int) ; 
 int stub1 (TYPE_4__*,int,int,int) ; 

__attribute__((used)) static int seek_frame_internal(AVFormatContext *s, int stream_index,
                               int64_t timestamp, int flags)
{
    int ret;
    AVStream *st;

    if (flags & AVSEEK_FLAG_BYTE) {
        if (s->iformat->flags & AVFMT_NO_BYTE_SEEK)
            return -1;
        ff_read_frame_flush(s);
        return seek_frame_byte(s, stream_index, timestamp, flags);
    }

    if (stream_index < 0) {
        stream_index = av_find_default_stream_index(s);
        if (stream_index < 0)
            return -1;

        st = s->streams[stream_index];
        /* timestamp for default must be expressed in AV_TIME_BASE units */
        timestamp = av_rescale(timestamp, st->time_base.den,
                               AV_TIME_BASE * (int64_t) st->time_base.num);
    }

    /* first, we try the format specific seek */
    if (s->iformat->read_seek) {
        ff_read_frame_flush(s);
        ret = s->iformat->read_seek(s, stream_index, timestamp, flags);
    } else
        ret = -1;
    if (ret >= 0)
        return 0;

    if (s->iformat->read_timestamp &&
        !(s->iformat->flags & AVFMT_NOBINSEARCH)) {
        ff_read_frame_flush(s);
        return ff_seek_frame_binary(s, stream_index, timestamp, flags);
    } else if (!(s->iformat->flags & AVFMT_NOGENSEARCH)) {
        ff_read_frame_flush(s);
        return seek_frame_generic(s, stream_index, timestamp, flags);
    } else
        return -1;
}