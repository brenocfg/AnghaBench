#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_8__ {int width; int height; int x_offset; int y_offset; int visible_width; int visible_height; } ;
typedef  TYPE_3__ VC_CONTAINER_VIDEO_FORMAT_T ;
struct TYPE_9__ {TYPE_2__* format; } ;
typedef  TYPE_4__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_BITS_T ;
struct TYPE_7__ {TYPE_1__* type; } ;
struct TYPE_6__ {TYPE_3__ video; } ;

/* Variables and functions */
 int BITS_READ_U32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int BITS_READ_U32_EXP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int BITS_READ_U8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  BITS_SKIP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  BITS_SKIP_EXP (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  BITS_VALID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int CHROMA_FORMAT_RGB ; 
 int CHROMA_FORMAT_YUV_444_PLANAR ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 int MACROBLOCK_HEIGHT ; 
 int MACROBLOCK_WIDTH ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int* chroma_sub_height ; 
 int* chroma_sub_width ; 
 int h264_get_chroma_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T h264_decode_sequence_parameter_set(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_T *track,
      VC_CONTAINER_BITS_T *sprop)
{
   VC_CONTAINER_VIDEO_FORMAT_T *video = &track->format->type->video;
   uint32_t pic_order_cnt_type, chroma_format_idc;
   uint32_t pic_width_in_mbs_minus1, pic_height_in_map_units_minus1, frame_mbs_only_flag;
   uint32_t frame_crop_left_offset, frame_crop_right_offset, frame_crop_top_offset, frame_crop_bottom_offset;
   uint8_t profile_idc;

   /* This structure is defined by H.264 section 7.3.2.1.1 */
   profile_idc = BITS_READ_U8(p_ctx, sprop, 8, "profile_idc");
   BITS_SKIP(p_ctx, sprop, 16, "Rest of profile_level_id");

   BITS_READ_U32_EXP(p_ctx, sprop, "seq_parameter_set_id");

   chroma_format_idc = CHROMA_FORMAT_RGB;
   if (profile_idc == 100 || profile_idc == 110 || profile_idc == 122 ||
         profile_idc == 244 || profile_idc == 44 || profile_idc == 83 ||
         profile_idc == 86 || profile_idc == 118 || profile_idc == 128)
   {
      chroma_format_idc = h264_get_chroma_format(p_ctx, sprop);
      if (chroma_format_idc > CHROMA_FORMAT_YUV_444_PLANAR)
         goto error;
   }

   BITS_SKIP_EXP(p_ctx, sprop, "log2_max_frame_num_minus4");
   pic_order_cnt_type = BITS_READ_U32_EXP(p_ctx, sprop, "pic_order_cnt_type");
   if (pic_order_cnt_type == 0)
   {
      BITS_SKIP_EXP(p_ctx, sprop, "log2_max_pic_order_cnt_lsb_minus4");
   }
   else if (pic_order_cnt_type == 1)
   {
      uint32_t num_ref_frames_in_pic_order_cnt_cycle;
      uint32_t ii;

      BITS_SKIP(p_ctx, sprop, 1, "delta_pic_order_always_zero_flag");
      BITS_SKIP_EXP(p_ctx, sprop, "offset_for_non_ref_pic");
      BITS_SKIP_EXP(p_ctx, sprop, "offset_for_top_to_bottom_field");
      num_ref_frames_in_pic_order_cnt_cycle = BITS_READ_U32_EXP(p_ctx, sprop, "num_ref_frames_in_pic_order_cnt_cycle");

      for (ii = 0; ii < num_ref_frames_in_pic_order_cnt_cycle; ii++)
         BITS_SKIP_EXP(p_ctx, sprop, "offset_for_ref_frame");
   }

   BITS_SKIP_EXP(p_ctx, sprop, "max_num_ref_frames");
   BITS_SKIP(p_ctx, sprop, 1, "gaps_in_frame_num_value_allowed_flag");

   pic_width_in_mbs_minus1 = BITS_READ_U32_EXP(p_ctx, sprop, "pic_width_in_mbs_minus1");
   pic_height_in_map_units_minus1 = BITS_READ_U32_EXP(p_ctx, sprop, "pic_height_in_map_units_minus1");
   frame_mbs_only_flag = BITS_READ_U32(p_ctx, sprop, 1, "frame_mbs_only_flag");

   /* Can now set the overall width and height in pixels */
   video->width = (pic_width_in_mbs_minus1 + 1) * MACROBLOCK_WIDTH;
   video->height = (2 - frame_mbs_only_flag) * (pic_height_in_map_units_minus1 + 1) * MACROBLOCK_HEIGHT;

   if (!frame_mbs_only_flag)
      BITS_SKIP(p_ctx, sprop, 1, "mb_adaptive_frame_field_flag");
   BITS_SKIP(p_ctx, sprop, 1, "direct_8x8_inference_flag");

   if (BITS_READ_U32(p_ctx, sprop, 1, "frame_cropping_flag"))
   {
      /* Visible area is restricted */
      frame_crop_left_offset = BITS_READ_U32_EXP(p_ctx, sprop, "frame_crop_left_offset");
      frame_crop_right_offset = BITS_READ_U32_EXP(p_ctx, sprop, "frame_crop_right_offset");
      frame_crop_top_offset = BITS_READ_U32_EXP(p_ctx, sprop, "frame_crop_top_offset");
      frame_crop_bottom_offset = BITS_READ_U32_EXP(p_ctx, sprop, "frame_crop_bottom_offset");

      /* Need to adjust offsets for 4:2:0 and 4:2:2 chroma formats and field/frame flag */
      frame_crop_left_offset *= chroma_sub_width[chroma_format_idc];
      frame_crop_right_offset *= chroma_sub_width[chroma_format_idc];
      frame_crop_top_offset *= chroma_sub_height[chroma_format_idc] * (2 - frame_mbs_only_flag);
      frame_crop_bottom_offset *= chroma_sub_height[chroma_format_idc] * (2 - frame_mbs_only_flag);

      if ((frame_crop_left_offset + frame_crop_right_offset) >= video->width ||
            (frame_crop_top_offset + frame_crop_bottom_offset) >= video->height)
      {
         LOG_ERROR(p_ctx, "H.264: frame crop offsets (%u, %u, %u, %u) larger than frame (%u, %u)",
               frame_crop_left_offset, frame_crop_right_offset, frame_crop_top_offset,
               frame_crop_bottom_offset, video->width, video->height);
         goto error;
      }

      video->x_offset = frame_crop_left_offset;
      video->y_offset = frame_crop_top_offset;
      video->visible_width = video->width - frame_crop_left_offset - frame_crop_right_offset;
      video->visible_height = video->height - frame_crop_top_offset - frame_crop_bottom_offset;
   } else {
      video->visible_width = video->width;
      video->visible_height = video->height;
   }

   /* vui_parameters may follow, but these will not be decoded */

   if (!BITS_VALID(p_ctx, sprop))
      goto error;

   return VC_CONTAINER_SUCCESS;

error:
   LOG_ERROR(p_ctx, "H.264: sequence_parameter_set failed to decode");
   return VC_CONTAINER_ERROR_FORMAT_INVALID;
}