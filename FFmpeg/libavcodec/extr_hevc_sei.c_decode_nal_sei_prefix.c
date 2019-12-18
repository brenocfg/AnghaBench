#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  alternative_transfer; int /*<<< orphan*/  content_light; int /*<<< orphan*/  mastering_display; int /*<<< orphan*/  display_orientation; int /*<<< orphan*/  frame_packing; int /*<<< orphan*/  picture_hash; } ;
typedef  TYPE_1__ HEVCSEI ;
typedef  int /*<<< orphan*/  HEVCParamSets ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
#define  HEVC_SEI_TYPE_ACTIVE_PARAMETER_SETS 135 
#define  HEVC_SEI_TYPE_ALTERNATIVE_TRANSFER_CHARACTERISTICS 134 
#define  HEVC_SEI_TYPE_CONTENT_LIGHT_LEVEL_INFO 133 
#define  HEVC_SEI_TYPE_DISPLAY_ORIENTATION 132 
#define  HEVC_SEI_TYPE_FRAME_PACKING 131 
#define  HEVC_SEI_TYPE_MASTERING_DISPLAY_INFO 130 
#define  HEVC_SEI_TYPE_PICTURE_TIMING 129 
#define  HEVC_SEI_TYPE_USER_DATA_REGISTERED_ITU_T_T35 128 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,int) ; 
 int decode_nal_sei_active_parameter_sets (TYPE_1__*,int /*<<< orphan*/ *,void*) ; 
 int decode_nal_sei_alternative_transfer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_nal_sei_content_light_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_nal_sei_decoded_picture_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_nal_sei_display_orientation (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_nal_sei_frame_packing_arrangement (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_nal_sei_mastering_display_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int decode_nal_sei_pic_timing (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*,int) ; 
 int decode_nal_sei_user_data_registered_itu_t_t35 (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_nal_sei_prefix(GetBitContext *gb, void *logctx, HEVCSEI *s,
                                 const HEVCParamSets *ps, int type, int size)
{
    switch (type) {
    case 256:  // Mismatched value from HM 8.1
        return decode_nal_sei_decoded_picture_hash(&s->picture_hash, gb);
    case HEVC_SEI_TYPE_FRAME_PACKING:
        return decode_nal_sei_frame_packing_arrangement(&s->frame_packing, gb);
    case HEVC_SEI_TYPE_DISPLAY_ORIENTATION:
        return decode_nal_sei_display_orientation(&s->display_orientation, gb);
    case HEVC_SEI_TYPE_PICTURE_TIMING:
        return decode_nal_sei_pic_timing(s, gb, ps, logctx, size);
    case HEVC_SEI_TYPE_MASTERING_DISPLAY_INFO:
        return decode_nal_sei_mastering_display_info(&s->mastering_display, gb);
    case HEVC_SEI_TYPE_CONTENT_LIGHT_LEVEL_INFO:
        return decode_nal_sei_content_light_info(&s->content_light, gb);
    case HEVC_SEI_TYPE_ACTIVE_PARAMETER_SETS:
        return decode_nal_sei_active_parameter_sets(s, gb, logctx);
    case HEVC_SEI_TYPE_USER_DATA_REGISTERED_ITU_T_T35:
        return decode_nal_sei_user_data_registered_itu_t_t35(s, gb, size);
    case HEVC_SEI_TYPE_ALTERNATIVE_TRANSFER_CHARACTERISTICS:
        return decode_nal_sei_alternative_transfer(&s->alternative_transfer, gb);
    default:
        av_log(logctx, AV_LOG_DEBUG, "Skipped PREFIX SEI %d\n", type);
        skip_bits_long(gb, 8 * size);
        return 0;
    }
}