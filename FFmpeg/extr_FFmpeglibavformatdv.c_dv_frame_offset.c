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
struct TYPE_10__ {TYPE_2__* internal; int /*<<< orphan*/  pb; } ;
struct TYPE_9__ {TYPE_1__* sys; } ;
struct TYPE_8__ {int data_offset; } ;
struct TYPE_7__ {int frame_size; } ;
typedef  TYPE_3__ DVDemuxContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int avio_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t dv_frame_offset(AVFormatContext *s, DVDemuxContext *c,
                               int64_t timestamp, int flags)
{
    // FIXME: sys may be wrong if last dv_read_packet() failed (buffer is junk)
    const int frame_size = c->sys->frame_size;
    int64_t offset;
    int64_t size       = avio_size(s->pb) - s->internal->data_offset;
    int64_t max_offset = ((size - 1) / frame_size) * frame_size;

    offset = frame_size * timestamp;

    if (size >= 0 && offset > max_offset)
        offset = max_offset;
    else if (offset < 0)
        offset = 0;

    return offset + s->internal->data_offset;
}