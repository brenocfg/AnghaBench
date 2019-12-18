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
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int io_repositioned; int /*<<< orphan*/  pb; TYPE_1__* internal; } ;
struct TYPE_4__ {scalar_t__ data_offset; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seek_frame_byte(AVFormatContext *s, int stream_index,
                           int64_t pos, int flags)
{
    int64_t pos_min, pos_max;

    pos_min = s->internal->data_offset;
    pos_max = avio_size(s->pb) - 1;

    if (pos < pos_min)
        pos = pos_min;
    else if (pos > pos_max)
        pos = pos_max;

    avio_seek(s->pb, pos, SEEK_SET);

    s->io_repositioned = 1;

    return 0;
}