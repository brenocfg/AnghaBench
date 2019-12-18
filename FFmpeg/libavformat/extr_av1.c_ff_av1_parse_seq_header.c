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
typedef  int /*<<< orphan*/  AV1SequenceParameters ;

/* Variables and functions */
#define  AV1_OBU_SEQUENCE_HEADER 128 
 int AVERROR_INVALIDDATA ; 
 int parse_obu_header (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int*,int*,int*,int*) ; 
 int parse_sequence_header (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int ff_av1_parse_seq_header(AV1SequenceParameters *seq, const uint8_t *buf, int size)
{
    int64_t obu_size;
    int start_pos, type, temporal_id, spatial_id;

    if (size <= 0)
        return AVERROR_INVALIDDATA;

    while (size > 0) {
        int len = parse_obu_header(buf, size, &obu_size, &start_pos,
                                   &type, &temporal_id, &spatial_id);
        if (len < 0)
            return len;

        switch (type) {
        case AV1_OBU_SEQUENCE_HEADER:
            if (!obu_size)
                return AVERROR_INVALIDDATA;

            return parse_sequence_header(seq, buf + start_pos, obu_size);
        default:
            break;
        }
        size -= len;
        buf  += len;
    }

    return AVERROR_INVALIDDATA;
}