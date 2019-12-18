#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int flags; scalar_t__ stream_index; int size; scalar_t__ pts; int /*<<< orphan*/  data; scalar_t__ side_data_elems; } ;
struct TYPE_11__ {scalar_t__ stream_id; int size_mul; scalar_t__ pts_delta; int header_idx; int flags; } ;
struct TYPE_10__ {int version; int max_distance; int* header_len; int /*<<< orphan*/ * header; } ;
struct TYPE_9__ {scalar_t__ last_pts; scalar_t__ max_pts_distance; } ;
typedef  TYPE_1__ StreamContext ;
typedef  TYPE_2__ NUTContext ;
typedef  TYPE_3__ FrameCode ;
typedef  TYPE_4__ AVPacket ;

/* Variables and functions */
 int AV_PKT_FLAG_KEY ; 
 scalar_t__ FFABS (scalar_t__) ; 
 int FLAG_CHECKSUM ; 
 int FLAG_CODED ; 
 int FLAG_CODED_PTS ; 
 int FLAG_HEADER_IDX ; 
 int FLAG_KEY ; 
 int FLAG_SIZE_MSB ; 
 int FLAG_SM_DATA ; 
 int FLAG_STREAM_ID ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_needed_flags(NUTContext *nut, StreamContext *nus, FrameCode *fc,
                            AVPacket *pkt)
{
    int flags = 0;

    if (pkt->flags & AV_PKT_FLAG_KEY)
        flags |= FLAG_KEY;
    if (pkt->stream_index != fc->stream_id)
        flags |= FLAG_STREAM_ID;
    if (pkt->size / fc->size_mul)
        flags |= FLAG_SIZE_MSB;
    if (pkt->pts - nus->last_pts != fc->pts_delta)
        flags |= FLAG_CODED_PTS;
    if (pkt->side_data_elems && nut->version > 3)
        flags |= FLAG_SM_DATA;
    if (pkt->size > 2 * nut->max_distance)
        flags |= FLAG_CHECKSUM;
    if (FFABS(pkt->pts - nus->last_pts) > nus->max_pts_distance)
        flags |= FLAG_CHECKSUM;
    if (fc->header_idx)
        if (pkt->size < nut->header_len[fc->header_idx] ||
            pkt->size > 4096                            ||
            memcmp(pkt->data, nut->header    [fc->header_idx],
                              nut->header_len[fc->header_idx]))
            flags |= FLAG_HEADER_IDX;

    return flags | (fc->flags & FLAG_CODED);
}