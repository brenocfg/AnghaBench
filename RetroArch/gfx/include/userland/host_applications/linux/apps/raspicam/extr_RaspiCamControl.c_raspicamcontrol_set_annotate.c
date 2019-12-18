#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  control; } ;
struct TYPE_5__ {int member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int enable; char* text; int text_size; int custom_text_Y; int custom_text_U; int custom_text_V; int custom_background_Y; int custom_background_U; int custom_background_V; unsigned int justify; unsigned int x_offset; unsigned int y_offset; int /*<<< orphan*/  hdr; void* custom_background_colour; void* custom_text_colour; void* enable_text_background; void* show_frame_num; void* show_motion; void* show_caf; void* show_lens; void* show_analog_gain; void* show_shutter; TYPE_1__ member_0; } ;
typedef  TYPE_2__ MMAL_PARAMETER_CAMERA_ANNOTATE_V4_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int const ANNOTATE_APP_TEXT ; 
 int const ANNOTATE_BLACK_BACKGROUND ; 
 int const ANNOTATE_CAF_SETTINGS ; 
 int const ANNOTATE_DATE_TEXT ; 
 int const ANNOTATE_FRAME_NUMBER ; 
 int const ANNOTATE_GAIN_SETTINGS ; 
 int const ANNOTATE_LENS_SETTINGS ; 
 int const ANNOTATE_MOTION_SETTINGS ; 
 int const ANNOTATE_SHUTTER_SETTINGS ; 
 int const ANNOTATE_TIME_TEXT ; 
 int const ANNOTATE_USER_TEXT ; 
 int MMAL_CAMERA_ANNOTATE_MAX_TEXT_LEN_V3 ; 
 int MMAL_CAMERA_ANNOTATE_MAX_TEXT_LEN_V4 ; 
 void* MMAL_FALSE ; 
 int /*<<< orphan*/  MMAL_PARAMETER_ANNOTATE ; 
 void* MMAL_TRUE ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_port_parameter_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mmal_status_to_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int /*<<< orphan*/  strftime (char*,int,char const*,struct tm*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int raspicamcontrol_set_annotate(MMAL_COMPONENT_T *camera, const int settings, const char *string,
                                 const int text_size, const int text_colour, const int bg_colour,
                                 const unsigned int justify, const unsigned int x, const unsigned int y)
{
   MMAL_PARAMETER_CAMERA_ANNOTATE_V4_T annotate =
   {{MMAL_PARAMETER_ANNOTATE, sizeof(MMAL_PARAMETER_CAMERA_ANNOTATE_V4_T)}};

   if (settings)
   {
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      char tmp[MMAL_CAMERA_ANNOTATE_MAX_TEXT_LEN_V4];
      int process_datetime = 1;

      annotate.enable = 1;

      if (settings & (ANNOTATE_APP_TEXT | ANNOTATE_USER_TEXT))
      {
         if ((settings & (ANNOTATE_TIME_TEXT | ANNOTATE_DATE_TEXT)) && strchr(string,'%') != NULL)
         {
            //string contains strftime parameter?
            strftime(annotate.text, MMAL_CAMERA_ANNOTATE_MAX_TEXT_LEN_V3, string, &tm );
            process_datetime = 0;
         }
         else
         {
            strncpy(annotate.text, string, MMAL_CAMERA_ANNOTATE_MAX_TEXT_LEN_V3);
         }
         annotate.text[MMAL_CAMERA_ANNOTATE_MAX_TEXT_LEN_V3-1] = '\0';
      }

      if (process_datetime && (settings & ANNOTATE_TIME_TEXT))
      {
         if(strlen(annotate.text))
         {
            strftime(tmp, 32, " %X", &tm );
         }
         else
         {
            strftime(tmp, 32, "%X", &tm );
         }
         strncat(annotate.text, tmp, MMAL_CAMERA_ANNOTATE_MAX_TEXT_LEN_V3 - strlen(annotate.text) - 1);
      }

      if (process_datetime && (settings & ANNOTATE_DATE_TEXT))
      {
         if(strlen(annotate.text))
         {
            strftime(tmp, 32, " %x", &tm );
         }
         else
         {
            strftime(tmp, 32, "%x", &tm );
         }
         strncat(annotate.text, tmp, MMAL_CAMERA_ANNOTATE_MAX_TEXT_LEN_V3 - strlen(annotate.text) - 1);
      }

      if (settings & ANNOTATE_SHUTTER_SETTINGS)
         annotate.show_shutter = MMAL_TRUE;

      if (settings & ANNOTATE_GAIN_SETTINGS)
         annotate.show_analog_gain = MMAL_TRUE;

      if (settings & ANNOTATE_LENS_SETTINGS)
         annotate.show_lens = MMAL_TRUE;

      if (settings & ANNOTATE_CAF_SETTINGS)
         annotate.show_caf = MMAL_TRUE;

      if (settings & ANNOTATE_MOTION_SETTINGS)
         annotate.show_motion = MMAL_TRUE;

      if (settings & ANNOTATE_FRAME_NUMBER)
         annotate.show_frame_num = MMAL_TRUE;

      if (settings & ANNOTATE_BLACK_BACKGROUND)
         annotate.enable_text_background = MMAL_TRUE;

      annotate.text_size = text_size;

      if (text_colour != -1)
      {
         annotate.custom_text_colour = MMAL_TRUE;
         annotate.custom_text_Y = text_colour&0xff;
         annotate.custom_text_U = (text_colour>>8)&0xff;
         annotate.custom_text_V = (text_colour>>16)&0xff;
      }
      else
         annotate.custom_text_colour = MMAL_FALSE;

      if (bg_colour != -1)
      {
         annotate.custom_background_colour = MMAL_TRUE;
         annotate.custom_background_Y = bg_colour&0xff;
         annotate.custom_background_U = (bg_colour>>8)&0xff;
         annotate.custom_background_V = (bg_colour>>16)&0xff;
      }
      else
         annotate.custom_background_colour = MMAL_FALSE;

      annotate.justify = justify;
      annotate.x_offset = x;
      annotate.y_offset = y;
   }
   else
      annotate.enable = 0;

   return mmal_status_to_int(mmal_port_parameter_set(camera->control, &annotate.hdr));
}