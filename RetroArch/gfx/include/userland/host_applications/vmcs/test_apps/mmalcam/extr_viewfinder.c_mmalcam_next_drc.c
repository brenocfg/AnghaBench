#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  drc_check ;
typedef  int /*<<< orphan*/  drc ;
struct TYPE_9__ {int /*<<< orphan*/  control; } ;
struct TYPE_7__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  strength; int /*<<< orphan*/  hdr; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PARAMETER_DRC_T ;
typedef  int /*<<< orphan*/  MMAL_PARAMETER_DRC_STRENGTH_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;
typedef  int /*<<< orphan*/  MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  MMAL_FALSE ; 
#define  MMAL_PARAMETER_DRC_STRENGTH_HIGH 131 
#define  MMAL_PARAMETER_DRC_STRENGTH_LOW 130 
#define  MMAL_PARAMETER_DRC_STRENGTH_MEDIUM 129 
#define  MMAL_PARAMETER_DRC_STRENGTH_OFF 128 
 int /*<<< orphan*/  MMAL_PARAMETER_DYNAMIC_RANGE_COMPRESSION ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 unsigned int countof (int /*<<< orphan*/  const*) ; 
 scalar_t__ memcmp (TYPE_2__*,TYPE_2__*,int) ; 
 scalar_t__ mmal_port_parameter_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_port_parameter_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_BOOL_T mmalcam_next_drc(MMAL_COMPONENT_T *camera)
{
   static const MMAL_PARAMETER_DRC_STRENGTH_T drc_setting[] = {
               MMAL_PARAMETER_DRC_STRENGTH_OFF,
               MMAL_PARAMETER_DRC_STRENGTH_LOW,
               MMAL_PARAMETER_DRC_STRENGTH_MEDIUM,
               MMAL_PARAMETER_DRC_STRENGTH_HIGH
            };
   static unsigned int index;
   MMAL_STATUS_T result;
   MMAL_PARAMETER_DRC_T drc = {{MMAL_PARAMETER_DYNAMIC_RANGE_COMPRESSION,sizeof(drc)},0};
   MMAL_PARAMETER_DRC_T drc_check = {{MMAL_PARAMETER_DYNAMIC_RANGE_COMPRESSION,sizeof(drc_check)},0};

   index++;
   if(index >= countof(drc_setting))
      index = 0;
   drc.strength = drc_setting[index];

   result = mmal_port_parameter_set(camera->control, &drc.hdr);
   if (result != MMAL_SUCCESS)
   {
      LOG_ERROR("Failed to set drc, %d", result);
      return MMAL_FALSE;
   }
   result = mmal_port_parameter_get(camera->control, &drc_check.hdr);
   if (result != MMAL_SUCCESS)
   {
      LOG_ERROR("Failed to retrieve drc, %d", result);
      return MMAL_FALSE;
   }
   if (memcmp(&drc, &drc_check, sizeof(drc)) != 0)
   {
      LOG_ERROR("DRC set (%d) was not retrieved (%d)", drc.strength, drc_check.strength);
      return MMAL_FALSE;
   }
   return MMAL_TRUE;
}