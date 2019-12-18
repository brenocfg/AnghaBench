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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 scalar_t__ rtp_get_parameter_u32 (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_check_unsupported_features(VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_T *track,
      const VC_CONTAINERS_LIST_T *params)
{
   uint32_t u32_unused;

   VC_CONTAINER_PARAM_UNUSED(p_ctx);
   VC_CONTAINER_PARAM_UNUSED(track);

   /* Limitation: RAP flag not yet supported */
   if (rtp_get_parameter_u32(params, "randomAccessIndication", &u32_unused))
   {
      LOG_ERROR(p_ctx, "MPEG-4: random access not supported");
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   }

   /* Limitation: interleaving not yet supported */
   if (rtp_get_parameter_u32(params, "maxDisplacement", &u32_unused) ||
         rtp_get_parameter_u32(params, "de-interleaveBufferSize", &u32_unused))
   {
      LOG_ERROR(p_ctx, "MPEG-4: interleaved packetization not supported");
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   }

   /* Limitation: system streams not supported */
   if (rtp_get_parameter_u32(params, "streamStateIndication", &u32_unused))
   {
      LOG_ERROR(p_ctx, "MPEG-4: system streams not supported");
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   }

   return VC_CONTAINER_SUCCESS;
}