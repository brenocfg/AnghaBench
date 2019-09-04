#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_18__ {TYPE_1__* priv_data; } ;
struct TYPE_17__ {scalar_t__ pict_type; } ;
struct TYPE_16__ {int size_in_bits; int /*<<< orphan*/  buffer; } ;
struct TYPE_15__ {int width; int height; int nonref; int frame_code; TYPE_2__ gb; } ;
typedef  TYPE_1__ SVQ1Context ;
typedef  TYPE_2__ GetBitContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 scalar_t__ AV_PICTURE_TYPE_P ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_4__*,char*,char*,int) ; 
 int** ff_svq1_frame_size_table ; 
 int ff_svq1_packet_checksum (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ get_bits (TYPE_2__*,int) ; 
 scalar_t__ get_bits1 (TYPE_2__*) ; 
 scalar_t__ skip_1stop_8data_bits (TYPE_2__*) ; 
 int /*<<< orphan*/  skip_bits (TYPE_2__*,int) ; 
 int /*<<< orphan*/  skip_bits1 (TYPE_2__*) ; 
 int /*<<< orphan*/  svq1_parse_string (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int svq1_decode_frame_header(AVCodecContext *avctx, AVFrame *frame)
{
    SVQ1Context *s = avctx->priv_data;
    GetBitContext *bitbuf = &s->gb;
    int frame_size_code;
    int width  = s->width;
    int height = s->height;

    skip_bits(bitbuf, 8); /* temporal_reference */

    /* frame type */
    s->nonref = 0;
    switch (get_bits(bitbuf, 2)) {
    case 0:
        frame->pict_type = AV_PICTURE_TYPE_I;
        break;
    case 2:
        s->nonref = 1;
    case 1:
        frame->pict_type = AV_PICTURE_TYPE_P;
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "Invalid frame type.\n");
        return AVERROR_INVALIDDATA;
    }

    if (frame->pict_type == AV_PICTURE_TYPE_I) {
        /* unknown fields */
        if (s->frame_code == 0x50 || s->frame_code == 0x60) {
            int csum = get_bits(bitbuf, 16);

            csum = ff_svq1_packet_checksum(bitbuf->buffer,
                                           bitbuf->size_in_bits >> 3,
                                           csum);

            ff_dlog(avctx, "%s checksum (%02x) for packet data\n",
                    (csum == 0) ? "correct" : "incorrect", csum);
        }

        if ((s->frame_code ^ 0x10) >= 0x50) {
            uint8_t msg[257];

            svq1_parse_string(bitbuf, msg);

            av_log(avctx, AV_LOG_INFO,
                   "embedded message:\n%s\n", ((char *)msg) + 1);
        }

        skip_bits(bitbuf, 2);
        skip_bits(bitbuf, 2);
        skip_bits1(bitbuf);

        /* load frame size */
        frame_size_code = get_bits(bitbuf, 3);

        if (frame_size_code == 7) {
            /* load width, height (12 bits each) */
            width  = get_bits(bitbuf, 12);
            height = get_bits(bitbuf, 12);

            if (!width || !height)
                return AVERROR_INVALIDDATA;
        } else {
            /* get width, height from table */
            width  = ff_svq1_frame_size_table[frame_size_code][0];
            height = ff_svq1_frame_size_table[frame_size_code][1];
        }
    }

    /* unknown fields */
    if (get_bits1(bitbuf)) {
        skip_bits1(bitbuf);    /* use packet checksum if (1) */
        skip_bits1(bitbuf);    /* component checksums after image data if (1) */

        if (get_bits(bitbuf, 2) != 0)
            return AVERROR_INVALIDDATA;
    }

    if (get_bits1(bitbuf)) {
        skip_bits1(bitbuf);
        skip_bits(bitbuf, 4);
        skip_bits1(bitbuf);
        skip_bits(bitbuf, 2);

        if (skip_1stop_8data_bits(bitbuf) < 0)
            return AVERROR_INVALIDDATA;
    }

    s->width  = width;
    s->height = height;
    return 0;
}