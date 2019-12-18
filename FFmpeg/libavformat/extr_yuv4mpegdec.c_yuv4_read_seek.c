#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_5__ {int packet_size; TYPE_1__* internal; int /*<<< orphan*/  pb; } ;
struct TYPE_4__ {scalar_t__ data_offset; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVSEEK_FLAG_BACKWARD ; 
 int FFMAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int yuv4_read_seek(AVFormatContext *s, int stream_index,
                          int64_t pts, int flags)
{
    int64_t pos;

    if (flags & AVSEEK_FLAG_BACKWARD)
        pts = FFMAX(0, pts - 1);
    if (pts < 0)
        return -1;
    pos = pts * s->packet_size;

    if (avio_seek(s->pb, pos + s->internal->data_offset, SEEK_SET) < 0)
        return -1;
    return 0;
}