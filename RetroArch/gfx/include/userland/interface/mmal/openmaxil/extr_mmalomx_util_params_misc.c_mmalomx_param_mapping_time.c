#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_3__ {int /*<<< orphan*/  nTimestamp; } ;
typedef  TYPE_1__ OMX_TIME_CONFIG_TIMESTAMPTYPE ;
typedef  scalar_t__ OMX_PTR ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PARAMETER_INT64_T ;
typedef  int /*<<< orphan*/  MMAL_PARAMETER_HEADER_T ;
typedef  scalar_t__ MMALOMX_PARAM_MAPPING_DIRECTION ;

/* Variables and functions */
 scalar_t__ MMALOMX_PARAM_MAPPING_TO_MMAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  omx_ticks_from_s64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omx_ticks_to_s64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static MMAL_STATUS_T mmalomx_param_mapping_time(MMALOMX_PARAM_MAPPING_DIRECTION dir,
   MMAL_PARAMETER_HEADER_T *mmal_param, OMX_PTR omx_param)
{
   OMX_TIME_CONFIG_TIMESTAMPTYPE *omx = (OMX_TIME_CONFIG_TIMESTAMPTYPE *)omx_param;
   MMAL_PARAMETER_INT64_T *mmal = (MMAL_PARAMETER_INT64_T *)mmal_param;

   if (dir == MMALOMX_PARAM_MAPPING_TO_MMAL)
      mmal->value = omx_ticks_to_s64(omx->nTimestamp);
   else
      omx->nTimestamp = omx_ticks_from_s64(mmal->value);

   return MMAL_SUCCESS;
}