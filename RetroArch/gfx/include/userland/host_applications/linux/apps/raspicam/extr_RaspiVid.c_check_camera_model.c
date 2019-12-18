#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  param ;
struct TYPE_10__ {int size; int /*<<< orphan*/  id; } ;
struct TYPE_9__ {int /*<<< orphan*/  control; } ;
struct TYPE_8__ {int num_cameras; TYPE_1__* cameras; TYPE_4__ hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  camera_name; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_2__ MMAL_PARAMETER_CAMERA_INFO_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_COMPONENT_DEFAULT_CAMERA_INFO ; 
 int /*<<< orphan*/  MMAL_PARAMETER_CAMERA_INFO ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mmal_component_create (int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  mmal_component_destroy (TYPE_3__*) ; 
 scalar_t__ mmal_port_parameter_get (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void check_camera_model(int cam_num)
{
   MMAL_COMPONENT_T *camera_info;
   MMAL_STATUS_T status;

   // Try to get the camera name
   status = mmal_component_create(MMAL_COMPONENT_DEFAULT_CAMERA_INFO, &camera_info);
   if (status == MMAL_SUCCESS)
   {
      MMAL_PARAMETER_CAMERA_INFO_T param;
      param.hdr.id = MMAL_PARAMETER_CAMERA_INFO;
      param.hdr.size = sizeof(param)-4;  // Deliberately undersize to check firmware version
      status = mmal_port_parameter_get(camera_info->control, &param.hdr);

      if (status != MMAL_SUCCESS)
      {
         // Running on newer firmware
         param.hdr.size = sizeof(param);
         status = mmal_port_parameter_get(camera_info->control, &param.hdr);
         if (status == MMAL_SUCCESS && param.num_cameras > cam_num)
         {
            if (!strncmp(param.cameras[cam_num].camera_name, "toshh2c", 7))
            {
               fprintf(stderr, "The driver for the TC358743 HDMI to CSI2 chip you are using is NOT supported.\n");
               fprintf(stderr, "They were written for a demo purposes only, and are in the firmware on an as-is\n");
               fprintf(stderr, "basis and therefore requests for support or changes will not be acted on.\n\n");
            }
         }
      }

      mmal_component_destroy(camera_info);
   }
}