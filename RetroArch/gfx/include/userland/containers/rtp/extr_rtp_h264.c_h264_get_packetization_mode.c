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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 scalar_t__ rtp_get_parameter_u32 (int /*<<< orphan*/  const*,char*,int*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T h264_get_packetization_mode(VC_CONTAINER_T *p_ctx,
      const VC_CONTAINERS_LIST_T *params)
{
   uint32_t packetization_mode;

   if (rtp_get_parameter_u32(params, "packetization-mode", &packetization_mode))
   {
      /* Only modes 0 and 1 are supported, no interleaving */
      if (packetization_mode > 1)
      {
         LOG_ERROR(p_ctx, "H.264: Unsupported packetization mode: %u", packetization_mode);
         return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
      }
   }

   return VC_CONTAINER_SUCCESS;
}