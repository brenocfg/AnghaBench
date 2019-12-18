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
struct TYPE_6__ {void* swap_eyes; void* decimate; int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {double x; double y; double w; double h; } ;
struct TYPE_7__ {int enable; int /*<<< orphan*/  v; int /*<<< orphan*/  u; } ;
struct TYPE_9__ {double sharpness; double contrast; double brightness; double saturation; double ISO; int videoStabilisation; double exposureCompensation; double rotation; int hflip; int vflip; double shutter_speed; double awb_gains_r; double awb_gains_b; unsigned int enable_annotate; char* annotate_string; double analog_gain; double digital_gain; int settings; TYPE_1__ stereo_mode; int /*<<< orphan*/  annotate_y; int /*<<< orphan*/  annotate_x; int /*<<< orphan*/  annotate_justify; int /*<<< orphan*/  annotate_bg_colour; int /*<<< orphan*/  annotate_text_colour; int /*<<< orphan*/  annotate_text_size; void* stats_pass; int /*<<< orphan*/  drc_level; TYPE_3__ roi; int /*<<< orphan*/  exposureMeterMode; TYPE_2__ colourEffects; int /*<<< orphan*/  imageEffect; int /*<<< orphan*/  awbMode; int /*<<< orphan*/  flickerAvoidMode; int /*<<< orphan*/  exposureMode; } ;
typedef  TYPE_4__ RASPICAM_CAMERA_PARAMETERS ;

/* Variables and functions */
 unsigned int ANNOTATE_USER_TEXT ; 
#define  CommandAWB 156 
#define  CommandAnalogGain 155 
#define  CommandAnnotate 154 
#define  CommandAnnotateExtras 153 
#define  CommandAwbGains 152 
#define  CommandBrightness 151 
#define  CommandColourFX 150 
#define  CommandContrast 149 
#define  CommandDRCLevel 148 
#define  CommandDigitalGain 147 
#define  CommandEVComp 146 
#define  CommandExposure 145 
#define  CommandFlicker 144 
#define  CommandHFlip 143 
#define  CommandISO 142 
#define  CommandImageFX 141 
#define  CommandMeterMode 140 
#define  CommandROI 139 
#define  CommandRotation 138 
#define  CommandSaturation 137 
#define  CommandSettings 136 
#define  CommandSharpness 135 
#define  CommandShutterSpeed 134 
#define  CommandStatsPass 133 
#define  CommandStereoDecimate 132 
#define  CommandStereoMode 131 
#define  CommandStereoSwap 130 
#define  CommandVFlip 129 
#define  CommandVideoStab 128 
 int /*<<< orphan*/  MMAL_CAMERA_ANNOTATE_MAX_TEXT_LEN_V3 ; 
 void* MMAL_TRUE ; 
 int /*<<< orphan*/  awb_mode_from_string (char const*) ; 
 int /*<<< orphan*/  cmdline_commands ; 
 int /*<<< orphan*/  cmdline_commands_size ; 
 int /*<<< orphan*/  drc_mode_from_string (char const*) ; 
 int /*<<< orphan*/  exposure_mode_from_string (char const*) ; 
 int /*<<< orphan*/  flicker_avoid_mode_from_string (char const*) ; 
 int /*<<< orphan*/  imagefx_mode_from_string (char const*) ; 
 int /*<<< orphan*/  metering_mode_from_string (char const*) ; 
 int raspicli_get_command_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int*) ; 
 int sscanf (char const*,char*,...) ; 
 int /*<<< orphan*/  stereo_mode_from_string (char const*) ; 

int raspicamcontrol_parse_cmdline(RASPICAM_CAMERA_PARAMETERS *params, const char *arg1, const char *arg2)
{
   int command_id, used = 0, num_parameters;

   if (!arg1)
      return 0;

   command_id = raspicli_get_command_id(cmdline_commands, cmdline_commands_size, arg1, &num_parameters);

   // If invalid command, or we are missing a parameter, drop out
   if (command_id==-1 || (command_id != -1 && num_parameters > 0 && arg2 == NULL))
      return 0;

   switch (command_id)
   {
   case CommandSharpness : // sharpness - needs single number parameter
      sscanf(arg2, "%d", &params->sharpness);
      used = 2;
      break;

   case CommandContrast : // contrast - needs single number parameter
      sscanf(arg2, "%d", &params->contrast);
      used = 2;
      break;

   case CommandBrightness : // brightness - needs single number parameter
      sscanf(arg2, "%d", &params->brightness);
      used = 2;
      break;

   case CommandSaturation : // saturation - needs single number parameter
      sscanf(arg2, "%d", &params->saturation);
      used = 2;
      break;

   case CommandISO : // ISO - needs single number parameter
      sscanf(arg2, "%d", &params->ISO);
      used = 2;
      break;

   case CommandVideoStab : // video stabilisation - if here, its on
      params->videoStabilisation = 1;
      used = 1;
      break;

   case CommandEVComp : // EV - needs single number parameter
      sscanf(arg2, "%d", &params->exposureCompensation);
      used = 2;
      break;

   case CommandExposure : // exposure mode - needs string
      params->exposureMode = exposure_mode_from_string(arg2);
      used = 2;
      break;

   case CommandFlicker : // flicker avoid mode - needs string
      params->flickerAvoidMode = flicker_avoid_mode_from_string(arg2);
      used = 2;
      break;

   case CommandAWB : // AWB mode - needs single number parameter
      params->awbMode = awb_mode_from_string(arg2);
      used = 2;
      break;

   case CommandImageFX : // Image FX - needs string
      params->imageEffect = imagefx_mode_from_string(arg2);
      used = 2;
      break;

   case CommandColourFX : // Colour FX - needs string "u:v"
      sscanf(arg2, "%d:%d", &params->colourEffects.u, &params->colourEffects.v);
      params->colourEffects.enable = 1;
      used = 2;
      break;

   case CommandMeterMode:
      params->exposureMeterMode = metering_mode_from_string(arg2);
      used = 2;
      break;

   case CommandRotation : // Rotation - degree
      sscanf(arg2, "%d", &params->rotation);
      used = 2;
      break;

   case CommandHFlip :
      params->hflip  = 1;
      used = 1;
      break;

   case CommandVFlip :
      params->vflip = 1;
      used = 1;
      break;

   case CommandROI :
   {
      double x,y,w,h;
      int args;

      args = sscanf(arg2, "%lf,%lf,%lf,%lf", &x,&y,&w,&h);

      if (args != 4 || x > 1.0 || y > 1.0 || w > 1.0 || h > 1.0)
      {
         return 0;
      }

      // Make sure we stay within bounds
      if (x + w > 1.0)
         w = 1 - x;

      if (y + h > 1.0)
         h = 1 - y;

      params->roi.x = x;
      params->roi.y = y;
      params->roi.w = w;
      params->roi.h = h;

      used = 2;
      break;
   }

   case CommandShutterSpeed : // Shutter speed needs single number parameter
   {
      sscanf(arg2, "%d", &params->shutter_speed);
      used = 2;
      break;
   }

   case CommandAwbGains :
   {
      double r,b;
      int args;

      args = sscanf(arg2, "%lf,%lf", &r,&b);

      if (args != 2 || r > 8.0 || b > 8.0)
      {
         return 0;
      }

      params->awb_gains_r = r;
      params->awb_gains_b = b;

      used = 2;
      break;
   }

   case CommandDRCLevel:
   {
      params->drc_level = drc_mode_from_string(arg2);
      used = 2;
      break;
   }

   case CommandStatsPass:
   {
      params->stats_pass = MMAL_TRUE;
      used = 1;
      break;
   }

   case CommandAnnotate:
   {
      char dummy;
      unsigned int bitmask;
      // If parameter is a number, assume its a bitmask, otherwise a string
      if (sscanf(arg2, "%u%c", &bitmask, &dummy) == 1)
      {
         params->enable_annotate |= bitmask;
      }
      else
      {
         params->enable_annotate |= ANNOTATE_USER_TEXT;
         //copy string char by char and replace "\n" with newline character
         unsigned char c;
         char const *s = arg2;
         char *t = &params->annotate_string[0];
         int n=0;
         while ((c = *s++) && n < MMAL_CAMERA_ANNOTATE_MAX_TEXT_LEN_V3-1)
         {
            if (c == '\\' && *s)
            {
               switch (c = *s++)
               {
               case 'n':
                  c = '\n';
                  break;

               default:
                  c = '\\';
                  s--;
                  break;
               }
            }
            *(t++) = c;
            n++;
         }
         *t='\0';

         //params->annotate_string[MMAL_CAMERA_ANNOTATE_MAX_TEXT_LEN_V3-1] = '\0';
      }
      used=2;
      break;
   }

   case CommandAnnotateExtras:
   {
      // 3 parameters - text size (6-80), text colour (Hex VVUUYY) and background colour (Hex VVUUYY)
      sscanf(arg2, "%u,%X,%X,%u,%u,%u", &params->annotate_text_size,
             &params->annotate_text_colour,
             &params->annotate_bg_colour,
             &params->annotate_justify,
             &params->annotate_x,
             &params->annotate_y
            );
      used=2;
      break;
   }

   case CommandStereoMode:
   {
      params->stereo_mode.mode = stereo_mode_from_string(arg2);
      used = 2;
      break;
   }

   case CommandStereoDecimate:
   {
      params->stereo_mode.decimate = MMAL_TRUE;
      used = 1;
      break;
   }

   case CommandStereoSwap:
   {
      params->stereo_mode.swap_eyes = MMAL_TRUE;
      used = 1;
      break;
   }

   case CommandAnalogGain:
   {
      double gain;
      int args;

      args = sscanf(arg2, "%lf", &gain);

      if (args != 1 || gain > 16.0)
      {
         return 0;
      }

      params->analog_gain = gain;

      used = 2;
      break;
   }
   case CommandDigitalGain:
   {
      double gain;
      int args;

      args = sscanf(arg2, "%lf", &gain);

      if (args != 1 || gain > 64.0)
      {
         return 0;
      }

      params->digital_gain = gain;

      used = 2;
      break;
   }

   case CommandSettings:
   {
      params->settings = 1;
      used = 1;
      break;
   }

   }

   return used;
}