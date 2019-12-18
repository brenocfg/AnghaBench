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
typedef  int /*<<< orphan*/  image_fx ;
struct TYPE_9__ {int /*<<< orphan*/  control; } ;
struct TYPE_7__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  value; int /*<<< orphan*/  hdr; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_PARAM_IMAGEFX_T ;
typedef  TYPE_2__ MMAL_PARAMETER_IMAGEFX_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;
typedef  int /*<<< orphan*/  MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  MMAL_FALSE ; 
 int /*<<< orphan*/  MMAL_PARAMETER_IMAGE_EFFECT ; 
#define  MMAL_PARAM_IMAGEFX_NEGATIVE 130 
#define  MMAL_PARAM_IMAGEFX_NONE 129 
#define  MMAL_PARAM_IMAGEFX_SOLARIZE 128 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 unsigned int countof (int /*<<< orphan*/  const*) ; 
 scalar_t__ memcmp (TYPE_2__*,TYPE_2__*,int) ; 
 scalar_t__ mmal_port_parameter_get (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ mmal_port_parameter_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static MMAL_BOOL_T mmalcam_next_effect(MMAL_COMPONENT_T *camera)
{
   static const MMAL_PARAM_IMAGEFX_T effects[] = {
               MMAL_PARAM_IMAGEFX_NONE,
               MMAL_PARAM_IMAGEFX_NEGATIVE,
               MMAL_PARAM_IMAGEFX_SOLARIZE
            };
   static unsigned int index;
   MMAL_PARAMETER_IMAGEFX_T image_fx = {{ MMAL_PARAMETER_IMAGE_EFFECT, sizeof(image_fx)},0};
   MMAL_PARAMETER_IMAGEFX_T image_fx_check = {{ MMAL_PARAMETER_IMAGE_EFFECT, sizeof(image_fx)},0};
   MMAL_STATUS_T result;

   index++;
   if(index >= countof(effects))
      index = 0;
   image_fx.value = effects[index];
   result = mmal_port_parameter_set(camera->control, &image_fx.hdr);
   if (result != MMAL_SUCCESS)
   {
      LOG_ERROR("Failed to set image effect, %d", result);
      return MMAL_FALSE;
   }
   result = mmal_port_parameter_get(camera->control, &image_fx_check.hdr);
   if (result != MMAL_SUCCESS)
   {
      LOG_ERROR("Failed to retrieve image effect, %d", result);
      return MMAL_FALSE;
   }
   if (memcmp(&image_fx, &image_fx_check, sizeof(image_fx)) != 0)
   {
      LOG_ERROR("Image effect set (%d) was not retrieved (%d)", image_fx.value, image_fx_check.value);
      return MMAL_FALSE;
   }
   return MMAL_TRUE;
}