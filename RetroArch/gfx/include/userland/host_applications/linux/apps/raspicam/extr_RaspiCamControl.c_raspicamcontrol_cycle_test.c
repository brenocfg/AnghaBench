#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  mmal_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  mmal_mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  mmal_mode; } ;
struct TYPE_6__ {int u; int v; int /*<<< orphan*/  enable; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ MMAL_PARAM_COLOURFX_T ;
typedef  int /*<<< orphan*/  MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAM_AWBMODE_AUTO ; 
 int /*<<< orphan*/  MMAL_PARAM_EXPOSUREMODE_AUTO ; 
 int /*<<< orphan*/  MMAL_PARAM_IMAGEFX_NONE ; 
 TYPE_5__* awb_map ; 
 int awb_map_size ; 
 TYPE_4__* exposure_map ; 
 int exposure_map_size ; 
 TYPE_3__* imagefx_map ; 
 int imagefx_map_size ; 
#define  parameter_reset 128 
 int /*<<< orphan*/  raspicamcontrol_set_awb_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raspicamcontrol_set_brightness (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  raspicamcontrol_set_colourFX (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  raspicamcontrol_set_contrast (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  raspicamcontrol_set_exposure_compensation (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  raspicamcontrol_set_exposure_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raspicamcontrol_set_flips (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  raspicamcontrol_set_imageFX (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raspicamcontrol_set_rotation (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  raspicamcontrol_set_saturation (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  raspicamcontrol_set_sharpness (int /*<<< orphan*/ *,int) ; 
 scalar_t__ update_cycle_parameter (int*,int,int,int) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ *) ; 

int raspicamcontrol_cycle_test(MMAL_COMPONENT_T *camera)
{
   static int parameter = 0;
   static int parameter_option = parameter_reset; // which value the parameter currently has

   vcos_assert(camera);

   // We are going to cycle through all the relevant entries in the parameter block
   // and send options to the camera.
   if (parameter == 0)
   {
      // sharpness
      if (update_cycle_parameter(&parameter_option, -100, 100, 10))
         raspicamcontrol_set_sharpness(camera, parameter_option);
      else
      {
         raspicamcontrol_set_sharpness(camera, 0);
         parameter++;
      }
   }
   else if (parameter == 1)
   {
      // contrast
      if (update_cycle_parameter(&parameter_option, -100, 100, 10))
         raspicamcontrol_set_contrast(camera, parameter_option);
      else
      {
         raspicamcontrol_set_contrast(camera, 0);
         parameter++;
      }
   }
   else if (parameter == 2)
   {
      // brightness
      if (update_cycle_parameter(&parameter_option, 0, 100, 10))
         raspicamcontrol_set_brightness(camera, parameter_option);
      else
      {
         raspicamcontrol_set_brightness(camera, 50);
         parameter++;
      }
   }
   else if (parameter == 3)
   {
      // contrast
      if (update_cycle_parameter(&parameter_option, -100, 100, 10))
         raspicamcontrol_set_saturation(camera, parameter_option);
      else
      {
         parameter++;
         raspicamcontrol_set_saturation(camera, 0);
      }
   }
   else if (parameter == 4)
   {
      // EV
      if (update_cycle_parameter(&parameter_option, -10, 10, 4))
         raspicamcontrol_set_exposure_compensation(camera, parameter_option);
      else
      {
         raspicamcontrol_set_exposure_compensation(camera, 0);
         parameter++;
      }
   }
   else if (parameter == 5)
   {
      // MMAL_PARAM_EXPOSUREMODE_T
      if (update_cycle_parameter(&parameter_option, 0, exposure_map_size, 1))
         raspicamcontrol_set_exposure_mode(camera, exposure_map[parameter_option].mmal_mode);
      else
      {
         raspicamcontrol_set_exposure_mode(camera, MMAL_PARAM_EXPOSUREMODE_AUTO);
         parameter++;
      }
   }
   else if (parameter == 6)
   {
      // MMAL_PARAM_AWB_T
      if (update_cycle_parameter(&parameter_option, 0, awb_map_size, 1))
         raspicamcontrol_set_awb_mode(camera, awb_map[parameter_option].mmal_mode);
      else
      {
         raspicamcontrol_set_awb_mode(camera, MMAL_PARAM_AWBMODE_AUTO);
         parameter++;
      }
   }
   if (parameter == 7)
   {
      // MMAL_PARAM_IMAGEFX_T
      if (update_cycle_parameter(&parameter_option, 0, imagefx_map_size, 1))
         raspicamcontrol_set_imageFX(camera, imagefx_map[parameter_option].mmal_mode);
      else
      {
         raspicamcontrol_set_imageFX(camera, MMAL_PARAM_IMAGEFX_NONE);
         parameter++;
      }
   }
   if (parameter == 8)
   {
      MMAL_PARAM_COLOURFX_T colfx = {0,0,0};
      switch (parameter_option)
      {
      case parameter_reset :
         parameter_option = 1;
         colfx.u = 128;
         colfx.v = 128;
         break;
      case 1 :
         parameter_option = 2;
         colfx.u = 100;
         colfx.v = 200;
         break;
      case 2 :
         parameter_option = parameter_reset;
         colfx.enable = 0;
         parameter++;
         break;
      }
      raspicamcontrol_set_colourFX(camera, &colfx);
   }

   // Orientation
   if (parameter == 9)
   {
      switch (parameter_option)
      {
      case parameter_reset:
         raspicamcontrol_set_rotation(camera, 90);
         parameter_option = 1;
         break;

      case 1 :
         raspicamcontrol_set_rotation(camera, 180);
         parameter_option = 2;
         break;

      case 2 :
         raspicamcontrol_set_rotation(camera, 270);
         parameter_option = 3;
         break;

      case 3 :
      {
         raspicamcontrol_set_rotation(camera, 0);
         raspicamcontrol_set_flips(camera, 1,0);
         parameter_option = 4;
         break;
      }
      case 4 :
      {
         raspicamcontrol_set_flips(camera, 0,1);
         parameter_option = 5;
         break;
      }
      case 5 :
      {
         raspicamcontrol_set_flips(camera, 1, 1);
         parameter_option = 6;
         break;
      }
      case 6 :
      {
         raspicamcontrol_set_flips(camera, 0, 0);
         parameter_option = parameter_reset;
         parameter++;
         break;
      }
      }
   }

   if (parameter == 10)
   {
      parameter = 1;
      return 0;
   }

   return 1;
}