#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
struct TYPE_32__ {int /*<<< orphan*/  control; } ;
struct TYPE_29__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_31__ {int member_2; int /*<<< orphan*/  hdr; int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
struct TYPE_30__ {scalar_t__ settings; int /*<<< orphan*/  digital_gain; int /*<<< orphan*/  analog_gain; int /*<<< orphan*/  annotate_y; int /*<<< orphan*/  annotate_x; int /*<<< orphan*/  annotate_justify; int /*<<< orphan*/  annotate_bg_colour; int /*<<< orphan*/  annotate_text_colour; int /*<<< orphan*/  annotate_text_size; int /*<<< orphan*/  annotate_string; int /*<<< orphan*/  enable_annotate; int /*<<< orphan*/  stats_pass; int /*<<< orphan*/  drc_level; int /*<<< orphan*/  shutter_speed; int /*<<< orphan*/  roi; int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; int /*<<< orphan*/  rotation; int /*<<< orphan*/  colourEffects; int /*<<< orphan*/  imageEffect; int /*<<< orphan*/  awb_gains_b; int /*<<< orphan*/  awb_gains_r; int /*<<< orphan*/  awbMode; int /*<<< orphan*/  exposureMeterMode; int /*<<< orphan*/  flickerAvoidMode; int /*<<< orphan*/  exposureMode; int /*<<< orphan*/  exposureCompensation; int /*<<< orphan*/  videoStabilisation; int /*<<< orphan*/  ISO; int /*<<< orphan*/  brightness; int /*<<< orphan*/  contrast; int /*<<< orphan*/  sharpness; int /*<<< orphan*/  saturation; } ;
typedef  TYPE_2__ RASPICAM_CAMERA_PARAMETERS ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_3__ MMAL_PARAMETER_CHANGE_EVENT_REQUEST_T ;
typedef  TYPE_4__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAMETER_CAMERA_SETTINGS ; 
 int /*<<< orphan*/  MMAL_PARAMETER_CHANGE_EVENT_REQUEST ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ mmal_port_parameter_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ raspicamcontrol_set_DRC (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_ISO (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_ROI (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_annotate (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_awb_gains (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_awb_mode (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_brightness (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_colourFX (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ raspicamcontrol_set_contrast (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_exposure_compensation (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_exposure_mode (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_flicker_avoid_mode (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_flips (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_gains (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_imageFX (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_metering_mode (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_rotation (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int raspicamcontrol_set_saturation (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_sharpness (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_shutter_speed (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_stats_pass (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ raspicamcontrol_set_video_stabilisation (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_error (char*) ; 

int raspicamcontrol_set_all_parameters(MMAL_COMPONENT_T *camera, const RASPICAM_CAMERA_PARAMETERS *params)
{
   int result;

   result  = raspicamcontrol_set_saturation(camera, params->saturation);
   result += raspicamcontrol_set_sharpness(camera, params->sharpness);
   result += raspicamcontrol_set_contrast(camera, params->contrast);
   result += raspicamcontrol_set_brightness(camera, params->brightness);
   result += raspicamcontrol_set_ISO(camera, params->ISO);
   result += raspicamcontrol_set_video_stabilisation(camera, params->videoStabilisation);
   result += raspicamcontrol_set_exposure_compensation(camera, params->exposureCompensation);
   result += raspicamcontrol_set_exposure_mode(camera, params->exposureMode);
   result += raspicamcontrol_set_flicker_avoid_mode(camera, params->flickerAvoidMode);
   result += raspicamcontrol_set_metering_mode(camera, params->exposureMeterMode);
   result += raspicamcontrol_set_awb_mode(camera, params->awbMode);
   result += raspicamcontrol_set_awb_gains(camera, params->awb_gains_r, params->awb_gains_b);
   result += raspicamcontrol_set_imageFX(camera, params->imageEffect);
   result += raspicamcontrol_set_colourFX(camera, &params->colourEffects);
   //result += raspicamcontrol_set_thumbnail_parameters(camera, &params->thumbnailConfig);  TODO Not working for some reason
   result += raspicamcontrol_set_rotation(camera, params->rotation);
   result += raspicamcontrol_set_flips(camera, params->hflip, params->vflip);
   result += raspicamcontrol_set_ROI(camera, params->roi);
   result += raspicamcontrol_set_shutter_speed(camera, params->shutter_speed);
   result += raspicamcontrol_set_DRC(camera, params->drc_level);
   result += raspicamcontrol_set_stats_pass(camera, params->stats_pass);
   result += raspicamcontrol_set_annotate(camera, params->enable_annotate, params->annotate_string,
                                          params->annotate_text_size,
                                          params->annotate_text_colour,
                                          params->annotate_bg_colour,
                                          params->annotate_justify,
                                          params->annotate_x,
                                          params->annotate_y);
   result += raspicamcontrol_set_gains(camera, params->analog_gain, params->digital_gain);

   if (params->settings)
   {
      MMAL_PARAMETER_CHANGE_EVENT_REQUEST_T change_event_request =
      {
         {MMAL_PARAMETER_CHANGE_EVENT_REQUEST, sizeof(MMAL_PARAMETER_CHANGE_EVENT_REQUEST_T)},
         MMAL_PARAMETER_CAMERA_SETTINGS, 1
      };

      MMAL_STATUS_T status = mmal_port_parameter_set(camera->control, &change_event_request.hdr);
      if ( status != MMAL_SUCCESS )
      {
         vcos_log_error("No camera settings events");
      }

      result += status;
   }

   return result;
}