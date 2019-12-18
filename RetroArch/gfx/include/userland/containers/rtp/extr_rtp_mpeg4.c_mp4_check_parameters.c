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
struct TYPE_8__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_9__ {int mode; int size_length; int index_length; int index_delta_length; int cts_delta_length; int dts_delta_length; int /*<<< orphan*/  constant_size; } ;
struct TYPE_7__ {TYPE_1__* module; } ;
struct TYPE_6__ {scalar_t__ extra; } ;
typedef  TYPE_4__ MP4_PAYLOAD_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,...) ; 
#define  MP4_AAC_HBR_MODE 131 
#define  MP4_AAC_LBR_MODE 130 
#define  MP4_CELP_CBR_MODE 129 
#define  MP4_CELP_VBR_MODE 128 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_check_parameters(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_T *track)
{
   MP4_PAYLOAD_T *extra = (MP4_PAYLOAD_T *)track->priv->module->extra;

   switch (extra->mode)
   {
   case MP4_CELP_CBR_MODE:
      if (!extra->constant_size)
      {
         LOG_ERROR(p_ctx, "MPEG-4: CELP-cbr requires constantSize parameter.");
         return VC_CONTAINER_ERROR_FORMAT_INVALID;
      }
      break;
   case MP4_CELP_VBR_MODE:
   case MP4_AAC_LBR_MODE:
      if (extra->size_length != 6 || extra->index_length != 2 || extra->index_delta_length != 2)
      {
         LOG_ERROR(p_ctx, "MPEG-4: CELP-vbr/AAC-lbr invalid lengths (%u/%u/%u)",
               extra->size_length, extra->index_length, extra->index_delta_length);
         return VC_CONTAINER_ERROR_FORMAT_INVALID;
      }
      break;
   case MP4_AAC_HBR_MODE:
      if (extra->size_length != 13 || extra->index_length != 3 || extra->index_delta_length != 3)
      {
         LOG_ERROR(p_ctx, "MPEG-4: AAC-hbr invalid lengths (%u/%u/%u)",
               extra->size_length, extra->index_length, extra->index_delta_length);
         return VC_CONTAINER_ERROR_FORMAT_INVALID;
      }
      break;
   default: /* MP4_GENERIC_MODE */
      if (extra->size_length > 32 || extra->index_length > 32 || extra->index_delta_length > 32)
      {
         LOG_ERROR(p_ctx, "MPEG-4: generic invalid lengths (%u/%u/%u)",
               extra->size_length, extra->index_length, extra->index_delta_length);
         return VC_CONTAINER_ERROR_FORMAT_INVALID;
      }
   }

   if (extra->cts_delta_length > 32 || extra->dts_delta_length > 32)
   {
      LOG_ERROR(p_ctx, "MPEG-4: CTS/DTS invalid lengths (%u/%u)",
            extra->cts_delta_length, extra->dts_delta_length);
      return VC_CONTAINER_ERROR_FORMAT_INVALID;
   }

   return VC_CONTAINER_SUCCESS;
}