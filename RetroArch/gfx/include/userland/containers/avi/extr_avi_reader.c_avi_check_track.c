#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_8__ {scalar_t__ tracks_num; TYPE_2__** tracks; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_7__ {TYPE_1__* format; } ;
struct TYPE_6__ {scalar_t__ es_type; } ;

/* Variables and functions */
 scalar_t__ AVI_TWOCC (char,char) ; 
 int /*<<< orphan*/  LOG_DEBUG (TYPE_3__*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FAILED ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_AUDIO ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_check_track(VC_CONTAINER_T *p_ctx, uint16_t data_type, uint16_t track_num)
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;

   if (track_num < p_ctx->tracks_num)
   {
      if (data_type == AVI_TWOCC('w','b') && p_ctx->tracks[track_num]->format->es_type != VC_CONTAINER_ES_TYPE_AUDIO)
      {
         LOG_DEBUG(p_ctx, "suspicious track type ('wb'), track %d is not an audio track", track_num);
         status = VC_CONTAINER_ERROR_FAILED;
      }
      if (data_type == AVI_TWOCC('d','b') && p_ctx->tracks[track_num]->format->es_type != VC_CONTAINER_ES_TYPE_VIDEO)
      {
         LOG_DEBUG(p_ctx, "suspicious track type ('db'), track %d is not a video track", track_num);
         status = VC_CONTAINER_ERROR_FAILED;
      }
      if (data_type == AVI_TWOCC('d','c') && p_ctx->tracks[track_num]->format->es_type != VC_CONTAINER_ES_TYPE_VIDEO)
      {
         LOG_DEBUG(p_ctx, "suspicious track type ('dc'), track %d is not a video track", track_num);
         status = VC_CONTAINER_ERROR_FAILED;
      }
      if (data_type == AVI_TWOCC('d','d') && p_ctx->tracks[track_num]->format->es_type != VC_CONTAINER_ES_TYPE_VIDEO)
      {
         LOG_DEBUG(p_ctx, "suspicious track type ('dd'), track %d is not a video track", track_num);
         status = VC_CONTAINER_ERROR_FAILED;
      }
   }
   else
   {
      LOG_DEBUG(p_ctx, "invalid track number %d (no more than %d tracks expected)",
         track_num, p_ctx->tracks_num);
      status = VC_CONTAINER_ERROR_FAILED;
   }

   return status;
}