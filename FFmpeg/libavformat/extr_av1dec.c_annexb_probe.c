#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_8__ {scalar_t__ error; scalar_t__ eof_reached; } ;
struct TYPE_7__ {int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ AVProbeData ;
typedef  TYPE_2__ AVIOContext ;

/* Variables and functions */
 int AV1_OBU_FRAME ; 
 int AV1_OBU_FRAME_HEADER ; 
 int AV1_OBU_SEQUENCE_HEADER ; 
 int AV1_OBU_TEMPORAL_DELIMITER ; 
 int AV1_OBU_TILE_GROUP ; 
 int AVPROBE_SCORE_EXTENSION ; 
 int /*<<< orphan*/  FFMIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  avio_skip (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ffio_init_context (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int leb (TYPE_2__*,scalar_t__*) ; 
 int read_obu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int*) ; 

__attribute__((used)) static int annexb_probe(const AVProbeData *p)
{
    AVIOContext pb;
    int64_t obu_size;
    uint32_t temporal_unit_size, frame_unit_size, obu_unit_size;
    int seq = 0, frame_header = 0;
    int ret, type, cnt = 0;

    ffio_init_context(&pb, p->buf, p->buf_size, 0,
                      NULL, NULL, NULL, NULL);

    ret = leb(&pb, &temporal_unit_size);
    if (ret < 0)
        return 0;
    cnt += ret;
    ret = leb(&pb, &frame_unit_size);
    if (ret < 0 || ((int64_t)frame_unit_size + ret) > temporal_unit_size)
        return 0;
    cnt += ret;
    temporal_unit_size -= ret;
    ret = leb(&pb, &obu_unit_size);
    if (ret < 0 || ((int64_t)obu_unit_size + ret) >= frame_unit_size)
        return 0;
    cnt += ret;

    temporal_unit_size -= obu_unit_size + ret;
    frame_unit_size -= obu_unit_size + ret;

    avio_skip(&pb, obu_unit_size);
    if (pb.eof_reached || pb.error)
        return 0;

    // Check that the first OBU is a Temporal Delimiter.
    ret = read_obu(p->buf + cnt, FFMIN(p->buf_size - cnt, obu_unit_size), &obu_size, &type);
    if (ret < 0 || type != AV1_OBU_TEMPORAL_DELIMITER || obu_size > 0)
        return 0;
    cnt += obu_unit_size;

    do {
        ret = leb(&pb, &obu_unit_size);
        if (ret < 0 || ((int64_t)obu_unit_size + ret) > frame_unit_size)
            return 0;
        cnt += ret;

        avio_skip(&pb, obu_unit_size);
        if (pb.eof_reached || pb.error)
            return 0;

        ret = read_obu(p->buf + cnt, FFMIN(p->buf_size - cnt, obu_unit_size), &obu_size, &type);
        if (ret < 0)
            return 0;
        cnt += obu_unit_size;

        if (type == AV1_OBU_SEQUENCE_HEADER)
            seq = 1;
        if (type == AV1_OBU_FRAME || type == AV1_OBU_FRAME_HEADER) {
            if (frame_header || !seq)
                return 0;
            frame_header = 1;
            break;
        }
        if (type == AV1_OBU_TILE_GROUP && !frame_header)
            return 0;

        temporal_unit_size -= obu_unit_size + ret;
        frame_unit_size -= obu_unit_size + ret;
    } while (!frame_header && frame_unit_size);

    return frame_header ? AVPROBE_SCORE_EXTENSION + 1 : 0;
}