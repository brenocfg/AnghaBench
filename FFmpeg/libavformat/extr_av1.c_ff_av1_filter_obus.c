#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
#define  AV1_OBU_PADDING 131 
#define  AV1_OBU_REDUNDANT_FRAME_HEADER 130 
#define  AV1_OBU_TEMPORAL_DELIMITER 129 
#define  AV1_OBU_TILE_LIST 128 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int parse_obu_header (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int*,int*,int*,int*) ; 

int ff_av1_filter_obus(AVIOContext *pb, const uint8_t *buf, int size)
{
    const uint8_t *end = buf + size;
    int64_t obu_size;
    int start_pos, type, temporal_id, spatial_id;

    size = 0;
    while (buf < end) {
        int len = parse_obu_header(buf, end - buf, &obu_size, &start_pos,
                                   &type, &temporal_id, &spatial_id);
        if (len < 0)
            return len;

        switch (type) {
        case AV1_OBU_TEMPORAL_DELIMITER:
        case AV1_OBU_REDUNDANT_FRAME_HEADER:
        case AV1_OBU_TILE_LIST:
        case AV1_OBU_PADDING:
            break;
        default:
            avio_write(pb, buf, len);
            size += len;
            break;
        }
        buf += len;
    }

    return size;
}