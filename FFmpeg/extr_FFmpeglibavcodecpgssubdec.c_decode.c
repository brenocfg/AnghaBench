#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_14__ {int err_recognition; } ;
struct TYPE_13__ {int* data; int size; } ;
struct TYPE_12__ {int /*<<< orphan*/  pts; } ;
typedef  TYPE_1__ AVSubtitle ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_EF_EXPLODE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  DISPLAY_SEGMENT 132 
#define  OBJECT_SEGMENT 131 
#define  PALETTE_SEGMENT 130 
#define  PRESENTATION_SEGMENT 129 
#define  WINDOW_SEGMENT 128 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 int bytestream_get_be16 (int const**) ; 
 int bytestream_get_byte (int const**) ; 
 int display_end_segment (TYPE_3__*,void*,int const*,int) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_3__*,char*,...) ; 
 int parse_object_segment (TYPE_3__*,int const*,int) ; 
 int parse_palette_segment (TYPE_3__*,int const*,int) ; 
 int parse_presentation_segment (TYPE_3__*,int const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode(AVCodecContext *avctx, void *data, int *data_size,
                  AVPacket *avpkt)
{
    const uint8_t *buf = avpkt->data;
    int buf_size       = avpkt->size;

    const uint8_t *buf_end;
    uint8_t       segment_type;
    int           segment_length;
    int i, ret;

    ff_dlog(avctx, "PGS sub packet:\n");

    for (i = 0; i < buf_size; i++) {
        ff_dlog(avctx, "%02x ", buf[i]);
        if (i % 16 == 15)
            ff_dlog(avctx, "\n");
    }

    if (i & 15)
        ff_dlog(avctx, "\n");

    *data_size = 0;

    /* Ensure that we have received at a least a segment code and segment length */
    if (buf_size < 3)
        return -1;

    buf_end = buf + buf_size;

    /* Step through buffer to identify segments */
    while (buf < buf_end) {
        segment_type   = bytestream_get_byte(&buf);
        segment_length = bytestream_get_be16(&buf);

        ff_dlog(avctx, "Segment Length %d, Segment Type %x\n", segment_length, segment_type);

        if (segment_type != DISPLAY_SEGMENT && segment_length > buf_end - buf)
            break;

        ret = 0;
        switch (segment_type) {
        case PALETTE_SEGMENT:
            ret = parse_palette_segment(avctx, buf, segment_length);
            break;
        case OBJECT_SEGMENT:
            ret = parse_object_segment(avctx, buf, segment_length);
            break;
        case PRESENTATION_SEGMENT:
            ret = parse_presentation_segment(avctx, buf, segment_length, ((AVSubtitle*)(data))->pts);
            break;
        case WINDOW_SEGMENT:
            /*
             * Window Segment Structure (No new information provided):
             *     2 bytes: Unknown,
             *     2 bytes: X position of subtitle,
             *     2 bytes: Y position of subtitle,
             *     2 bytes: Width of subtitle,
             *     2 bytes: Height of subtitle.
             */
            break;
        case DISPLAY_SEGMENT:
            if (*data_size) {
                av_log(avctx, AV_LOG_ERROR, "Duplicate display segment\n");
                ret = AVERROR_INVALIDDATA;
                break;
            }
            ret = display_end_segment(avctx, data, buf, segment_length);
            if (ret >= 0)
                *data_size = ret;
            break;
        default:
            av_log(avctx, AV_LOG_ERROR, "Unknown subtitle segment type 0x%x, length %d\n",
                   segment_type, segment_length);
            ret = AVERROR_INVALIDDATA;
            break;
        }
        if (ret < 0 && (avctx->err_recognition & AV_EF_EXPLODE))
            return ret;

        buf += segment_length;
    }

    return buf_size;
}