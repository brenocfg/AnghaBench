#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ gxf_resync_media (TYPE_1__*,scalar_t__,int,int) ; 

__attribute__((used)) static int64_t gxf_read_timestamp(AVFormatContext *s, int stream_index,
                                  int64_t *pos, int64_t pos_limit) {
    AVIOContext *pb = s->pb;
    int64_t res;
    if (avio_seek(pb, *pos, SEEK_SET) < 0)
        return AV_NOPTS_VALUE;
    res = gxf_resync_media(s, pos_limit - *pos, -1, -1);
    *pos = avio_tell(pb);
    return res;
}