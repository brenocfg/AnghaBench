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
struct TYPE_4__ {int /*<<< orphan*/  alternative_transfer; int /*<<< orphan*/  green_metadata; int /*<<< orphan*/  display_orientation; int /*<<< orphan*/  frame_packing; int /*<<< orphan*/  buffering_period; int /*<<< orphan*/  recovery_point; int /*<<< orphan*/  unregistered; int /*<<< orphan*/  picture_timing; } ;
typedef  TYPE_1__ H264SEIContext ;
typedef  int /*<<< orphan*/  H264ParamSets ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PS_NOT_FOUND ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  H264_SEI_TYPE_ALTERNATIVE_TRANSFER 136 
#define  H264_SEI_TYPE_BUFFERING_PERIOD 135 
#define  H264_SEI_TYPE_DISPLAY_ORIENTATION 134 
#define  H264_SEI_TYPE_FRAME_PACKING 133 
#define  H264_SEI_TYPE_GREEN_METADATA 132 
#define  H264_SEI_TYPE_PIC_TIMING 131 
#define  H264_SEI_TYPE_RECOVERY_POINT 130 
#define  H264_SEI_TYPE_USER_DATA_REGISTERED 129 
#define  H264_SEI_TYPE_USER_DATA_UNREGISTERED 128 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,int,...) ; 
 int decode_alternative_transfer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_buffering_period (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*) ; 
 int decode_display_orientation (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_frame_packing_arrangement (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_green_metadata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_picture_timing (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*) ; 
 int decode_recovery_point (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int decode_registered_user_data (TYPE_1__*,int /*<<< orphan*/ *,void*,unsigned int) ; 
 int decode_unregistered_user_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,unsigned int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 unsigned int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 scalar_t__ show_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,unsigned int) ; 

int ff_h264_sei_decode(H264SEIContext *h, GetBitContext *gb,
                       const H264ParamSets *ps, void *logctx)
{
    int master_ret = 0;

    while (get_bits_left(gb) > 16 && show_bits(gb, 16)) {
        int type = 0;
        unsigned size = 0;
        unsigned next;
        int ret  = 0;

        do {
            if (get_bits_left(gb) < 8)
                return AVERROR_INVALIDDATA;
            type += show_bits(gb, 8);
        } while (get_bits(gb, 8) == 255);

        do {
            if (get_bits_left(gb) < 8)
                return AVERROR_INVALIDDATA;
            size += show_bits(gb, 8);
        } while (get_bits(gb, 8) == 255);

        if (size > get_bits_left(gb) / 8) {
            av_log(logctx, AV_LOG_ERROR, "SEI type %d size %d truncated at %d\n",
                   type, 8*size, get_bits_left(gb));
            return AVERROR_INVALIDDATA;
        }
        next = get_bits_count(gb) + 8 * size;

        switch (type) {
        case H264_SEI_TYPE_PIC_TIMING: // Picture timing SEI
            ret = decode_picture_timing(&h->picture_timing, gb, ps, logctx);
            break;
        case H264_SEI_TYPE_USER_DATA_REGISTERED:
            ret = decode_registered_user_data(h, gb, logctx, size);
            break;
        case H264_SEI_TYPE_USER_DATA_UNREGISTERED:
            ret = decode_unregistered_user_data(&h->unregistered, gb, logctx, size);
            break;
        case H264_SEI_TYPE_RECOVERY_POINT:
            ret = decode_recovery_point(&h->recovery_point, gb, logctx);
            break;
        case H264_SEI_TYPE_BUFFERING_PERIOD:
            ret = decode_buffering_period(&h->buffering_period, gb, ps, logctx);
            break;
        case H264_SEI_TYPE_FRAME_PACKING:
            ret = decode_frame_packing_arrangement(&h->frame_packing, gb);
            break;
        case H264_SEI_TYPE_DISPLAY_ORIENTATION:
            ret = decode_display_orientation(&h->display_orientation, gb);
            break;
        case H264_SEI_TYPE_GREEN_METADATA:
            ret = decode_green_metadata(&h->green_metadata, gb);
            break;
        case H264_SEI_TYPE_ALTERNATIVE_TRANSFER:
            ret = decode_alternative_transfer(&h->alternative_transfer, gb);
            break;
        default:
            av_log(logctx, AV_LOG_DEBUG, "unknown SEI type %d\n", type);
        }
        if (ret < 0 && ret != AVERROR_PS_NOT_FOUND)
            return ret;
        if (ret < 0)
            master_ret = ret;

        skip_bits_long(gb, next - get_bits_count(gb));

        // FIXME check bits here
        align_get_bits(gb);
    }

    return master_ret;
}