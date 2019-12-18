#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_3__ {int /*<<< orphan*/ * pb; } ;
typedef  scalar_t__ GXFPktType ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int AV_NOPTS_VALUE ; 
 scalar_t__ PKT_MEDIA ; 
 int /*<<< orphan*/  READ_ONE () ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_packet_header (int /*<<< orphan*/ *,scalar_t__*,int*) ; 

__attribute__((used)) static int64_t gxf_resync_media(AVFormatContext *s, uint64_t max_interval, int track, int timestamp) {
    uint32_t tmp;
    uint64_t last_pos;
    uint64_t last_found_pos = 0;
    int cur_track;
    int64_t cur_timestamp = AV_NOPTS_VALUE;
    int len;
    AVIOContext *pb = s->pb;
    GXFPktType type;
    tmp = avio_rb32(pb);
start:
    while (tmp)
        READ_ONE();
    READ_ONE();
    if (tmp != 1)
        goto start;
    last_pos = avio_tell(pb);
    if (avio_seek(pb, -5, SEEK_CUR) < 0)
        goto out;
    if (!parse_packet_header(pb, &type, &len) || type != PKT_MEDIA) {
        if (avio_seek(pb, last_pos, SEEK_SET) < 0)
            goto out;
        goto start;
    }
    avio_r8(pb);
    cur_track = avio_r8(pb);
    cur_timestamp = avio_rb32(pb);
    last_found_pos = avio_tell(pb) - 16 - 6;
    if ((track >= 0 && track != cur_track) || (timestamp >= 0 && timestamp > cur_timestamp)) {
        if (avio_seek(pb, last_pos, SEEK_SET) >= 0)
            goto start;
    }
out:
    if (last_found_pos)
        avio_seek(pb, last_found_pos, SEEK_SET);
    return cur_timestamp;
}